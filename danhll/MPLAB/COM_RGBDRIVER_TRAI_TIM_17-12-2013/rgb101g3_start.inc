; ******************************************************************************************************
; Initialisation and startup code block
; ------------------------------------------------------------------------------------------------------

_startup

       
                clrf            GPIO
 
                setbank1                        ; switch to register bank 1
                movlw           ~(1<<red | 1<<green | 1<<blue ) ; Set up W for output bits
                movwf           TRISIO
                
  IFDEF OSCCAL                                  ; defined only for 12F629 / 675
                call            0x3FF           ; read factory oscillator calibration value
                movwf           OSCCAL          ; write to OSCCAL register
                                                ; If using a 12F629/675 this value must be present
                                                ; and correct, or the code will not function properly
                                                ; if it functions at all.
  ENDIF

  IFDEF ADCpresent
                clrf            ANSEL           ; Set ports for digital mode (12F675 / 12F683 only)
  ENDIF
                                
                movlw           b'00000000'     ;setup option register
                ;                 ||||||||---- PS0 - Timer 0: Prescalar 1:64
                ;                 |||||||----- PS1 - .......
                ;                 ||||||------ PS2 - .......
                ;                 |||||------- PSA -  Assign prescaler to Timer0
                ;                 ||||-------- TOSE - LtoH edge          (Don't care)
                ;                 |||--------- TOCS - Timer0 uses IntClk (Don't care)
                ;                 ||---------- INTEDG - falling edge RB0 (Don't care)
                ;                 |----------- GPPU - pull-ups enabled 
                movwf           OPTION_REG

                bsf             WPU,seqSw       ; enable weak-pull-up for seqSw input
                bsf             WPU,auxIn       ; enable weak-pull-up on auxIn input
                                                ; GPIO3 has no weak-pull-up feature

                bsf             IOC,seqSw       ; Enable Interrupt-on-change for seqSw input

                setbank0
                
                movlw           0x07            ; load W=7
  IFDEF __12F683
                movwf           CMCON0          ; disable Comparator on 12F683
  ELSE
                movwf           CMCON           ; disable Comparator on 12F675/627
  ENDIF
                bsf             INTCON,GPIE     ; Enable Interrupt-on-change (to wake PIC from sleep)

                ; Clear GPR memory
                ; ---------------------------------------------------------------
                
                movlw           0x20            ; load W with address of first GPR memory
                movwf           FSR             ; save in FSR indirection register
                movwf           0x5F            ; save a non-zero value to last GPR memory (addr 0x5F)
_clrNext        clrf            INDF            ; clear contents of register pointed to by FSR
                incf            FSR,F           ; increment FSR
                movf            0x5F,F          ; Test value in last GPR memory location
                skpz                            ; skip next if last GPR has been cleared
                goto            _clrNext        ; otherwise, repeat until done.

                ; Initialise specific variables
                ; ---------------------------------------------------------------
                call            _advResetBase
                movlw           cTIMER
                movwf           TMR0
                bcf             INTCON,T0IF
                movlw           cHOLDPRESCALER
                movwf           holdTimerPS
                

                ; ---------------------------------------------------------------
                ; Find how many sequences are available
                ; Get last sequence in use from EEPROM
                ; verify it is equal to or less than available number of sequences
                ; initialise current sequence data
                
                
_findNoSeq      call            _advSeq         ; advance to next available sequence
                bnz             _getSavedSeq    ; branch out if W != 0. Reached last sequence
                incf            highSeqNo,F     ; else increment high sequence counter
                goto            _findNoSeq      ; and repeat.

_getSavedSeq    call            _readEEPROM      ; read saved sequence No from EEPROM
	bz	_checksumOK
	call	_initEEPROM
	goto	_getSavedSeq 	

_checksumOK	movfw           savedSeqNo      ; write to saved Sequence No
                subwf           highSeqNo,W     ; compare to highest available seq
                skpc             	; branch if saved <= highest
                call            _initEEPROM     ; and save to EEPROM
                
                                
_compSeqNo      movfw           savedSeqNo      ; put saved sequence No into W reg
                xorwf           currentSeqNo,W  ; compare to current sequence No
                bz              _seqSet         ; branch if match
                call            _advSeq         ; else advance to next sequence
                goto            _compSeqNo      ; and compare again
_seqSet	call            _seqData        ; initialise first sequence data
	btfss	freeze,0        ; if freeze active, skip fade initialisation
	call            _fadeDir        ; initialise fade direction
              
	movlw           0xFF            ; set LED drive to active Low    


  
                goto            _pwmDriveHi       ; Go and run the main code