; PWM LED Chaser 
; All functions used by PWM LED Chaser are contained in this include file
; rev 1.0.2

;--------------------------------------------------------------------------------------------------------------------
; PWM Function


_pwm          movfw         vc0           ; AND all 5 bits of vertical counter
              andwf         vc1,W
              andwf         vc2,W
              andwf         vc3,W
              andwf         vc4,W
              iorwf         copyPORTB,F   ; then OR bits with copyPORTB working variable
              movfw         copyPORTB     ; load in W
              movwf         PORTB         ; and write to physical PORTB
                                          ; when 5 bits in vertical count reach 11111 
                                          ; corresponding Port bit is turned on and then
                                          ; remains on until counter is reset
              
; ---------------------------------------
; 2^5 bit x 8 vertical counter
; generates the pwm for the 8 channel LED output
; More info on how this works can be found here
;  http://everything2.com/e2node/vertical counter
;  http://www.dattalo.com/technical/software/pic/vertcnt.html

_vc32         movf          vc3,W
              andwf         vc2,W
              andwf         vc1,W
              andwf         vc0,W
              xorwf         vc4,F

              movf          vc2,W
              andwf         vc1,W
              andwf         vc0,W
              xorwf         vc3,F

              movf          vc1,W
              andwf         vc0,W
              xorwf         vc2,F

              movf          vc0,W
              xorwf         vc1,F

              comf          vc0,F

; ---------------------------------------

              decfsz        pwm,F         ; decrement PWM counter
              return                      ; return if count != 0

              ; reset and reload PWM output / counter
              movlw         .31           ; reload PWM counter
              movwf         pwm
              
              clrf          copyPORTB     ; reset output port working variable
              ; vertical counter is 8 channels by 5 bits
              ; rvc1 rvc0  vc4-0  PWM ratio
              ;    0 0     00000  0/31   off
              ;    0 1     00001  1/31   dim
              ;    1 0     00100  8/31   bright
              ;    1 1     11111  31/31  very bright
              ;
              movfw         loReload      ; reload the  vertical counter
              movwf         vc0           
              movfw         hiReload
              movwf         vc3
              andwf         loReload,W
              movwf         vc1
              movwf         vc2
              movwf         vc4
              return

       
;--------------------------------------------------------------------------------------------------------------------
; function to reverse the bits in the data
; bits 7-0 -> 0-7
; Use inline code rather than loop for speed.

_mirrorData   movwf         forward       ; enter with data to reverse in W
              rlf           forward,f ;0
              rrf           reverse,f
              rlf           forward,f ;1
              rrf           reverse,f
              rlf           forward,f ;2
              rrf           reverse,f
              rlf           forward,f ;3
              rrf           reverse,f
              rlf           forward,f ;4
              rrf           reverse,f
              rlf           forward,f ;5
              rrf           reverse,f
              rlf           forward,f ;6
              rrf           reverse,f
              rlf           forward,f ;7
              rrf           reverse,w     ;return with reversed data in W
              return
              
              
;--------------------------------------------------------------------------------------------------------------------
; LOOKUP function

_Lookup       call          _incTableRd
	clrf	PCLATH
              movwf         holdTime                    ; save holdTimer variable
              bcf           flags, fHoldTimeout         ; clear holdTimeout flag
              addlw         .1                          ; add 1 to holdTime, if it was 255 result is 0 carry 1
              skpnz                                     ; skip next if result is not 0
              goto          _resetIndex                 ; otherwise we've reached end of data so reset points to start
              
              call          _incTableRd
	clrf	PCLATH
              btfsc         flags, fMirrorData
              call          _mirrorData
              movwf         reloadTemp

              call          _incTableRd
	clrf	PCLATH
              btfsc         flags, fMirrorData
              call          _mirrorData
	movwf         hiReload
              movfw         reloadTemp
              movwf         loReload
              return
;-------------------------------------------
; reset index to start of sequence, read first entry (repeat count / mirror flag) and
; discard it so we set index pointer to first line entry of sequence
; Also set hold timeout flag so we come straight back into the lookup function on next state run
_resetIndex   call          _setSeqBase                 ;
              call          _incTableRd                 ; read repeatcount but ignore it
	clrf	PCLATH
              decf          repeatCount,F               ; instead decrement current repeatCount value
              bsf           flags, fHoldTimeout         ; set hold timeout flag so state function
                                                        ; doesn't wait after sequence restarts
              return                                    

;--------------------------------------------
; set index to start of sequence, read first entry (repeat count / mirror flag) and
; save it to repeatCount variable
;
_setIndex     call          _setSeqBase   ; initialise index pointer
              call          _incTableRd   ; read first entry of sequence
	clrf	PCLATH
              movwf         repeatCount   ; save into repeatcCount variable
              
              return

;--------------------------------------------
; _countSeqIn function dynamically locates base address of each sequence
; in the sequence data table.  
; We need to transfer the base address found by _countSeqIn funtion to 
; working base address used by Lookup function

_setSeqBase   movfw         seqIdxHi
              movwf         indexHi
              movfw         seqIdxLo
              movwf         indexLo
              return

_incTableRd   movfw         indexHi
              movwf         PCLATH
              movfw         indexLo
              incf          indexLo,F
              skpnz
              incf          indexHi,F
              movwf         PCL


;-------------------------------------------------------
; Function searches through data table to either
; a) find number of individual sequences in data 
; b) set index to start address of specific sequence
;
; Since sequence data is user defined we don't know how many there are or where each one
; starts in program memory.  This function will find the total number of sequences or
; the base start address of a specific sequence
;
; To find total entries call with W == 255  ( assume there are no more than 254 sequences)
; To set index to a specific sequence start address, call with W == SeqNo (counting from 0)
; for example, if the number there are 5 sequences then they are numbered 0,1,2,3,4
; 
; There is no validity checking in this function so if it is asked to match a sequence number
; higher than the total sequences available it will return with the index address pointing
; past the end of valid data. (expect the application to crash )
; Do not call with W > total_seqences-1 unless you want to find the total number of sequences
; 

_countSeqIn   movwf         seqMatch                    ; save sequence match number
              call          _countRstIdx                ; reset index to point to sequence data start address
              movf          seqMatch,F                  ; Test for 0. Are we looking for first sequence?
              skpnz                                     ; if not skip to search
              return                                    ; else return (index initialised to first entry)
              movwf         seqIdxHi
              clrf          seqCount
_countSeqLp   call          _seqTableRd   ; read control field
	clrf	PCLATH
              addlw         0x01          ; test for data == .255
              bz            _foundEnd
              movlw         .3
              skpnz
_readNext     movlw         .2
              addwf         seqIdxLo,F
              skpnc
              incf          seqIdxHi,F

              call          _seqTableRd
	clrf	PCLATH
              addlw         0x01
              skpz          
              goto          _readNext

              incf          seqCount,W
              movwf         seqCount
              xorwf         seqMatch,W
              skpz
              goto          _countSeqLp
              return
              
_foundEnd     movfw         seqCount
              movwf         seqTotal

_countRstIdx  movlw         LOW SeqBaseAddr             ; initialise index to table base
              movwf         seqIdxLo
              movlw         HIGH SeqBaseAddr
              movwf         seqIdxHi
              return

_seqTableRd   movfw         seqIdxHi
              movwf         PCLATH
              movfw         seqIdxLo
              incf          seqIdxLo,F
              skpnz
              incf          seqIdxHi,F
              movwf         PCL

;--------------------------------------------------------------------------------------------------------------------
; Random number generator code
; Implementations of the Galois LFSR (Linear Feedback Shift Register)
; 16-bit random number generator (tested)
; The 0xA1 is part of a prime polynom value 0xA1A1 which generates a full LFSR
; Code credited to Mark Jeronimus of Digital Mosular
; http://www.piclist.com/techref/microchip/rand8bit.htm
;

_randNum      movfw         LFSRH         ; test if LFSR is zero
              iorwf         LFSRL,W
              skpnz                       ; skip next if it isn't
              comf          LFSRL,F       ; restart it if it was
              clrc
              rlf           LFSRH,F
              rlf           LFSRL,F
              skpc
              goto          _randExit
              movlw         0xA1
              xorwf         LFSRH,F
              xorwf         LFSRL,F    
_randExit     movfw         LFSRL       
              return

;--------------------------------------------------------------------------------------------------------------------
; Save and Restore operating mode and active sequence to/from EEPROM
;
; Read two bytes from EEPROM
; EEPROM Addr 0x00 holds saved seqMatch == current selected sequence
; EEPROM Addr 0x01 holds saved mode ==  current operating mode
; EEPROM Addr 0x02 holds saved flags ==  for mirror flag bit

restore.opmode
	clrw		;eeprom address 0
	call	eeprom.read
	subwf	seqTotal,W
	movfw	eesave_W
	skpc
	clrw
	movwf	seqMatch
	call	_countSeqIn
	call	_setIndex

	movlw	0x01	; eeprom address 1
	call	eeprom.read
	andlw	(1<<modeSeq | 1<<modeRan | 1<<modeMan )
	movwf	eesave_W
	movwf	mode

	clrw

	rrf	eesave_W,F
	skpnc	
	addlw	.1

	rrf	eesave_W,F
	skpnc	
	addlw	.1

	rrf	eesave_W,F
	skpnc	
	addlw	.1

	addlw	-.1
	skpnz
	goto	restore.flags
	movlw	1<<modeSeq
	movwf	mode


restore.flags	movlw	0x02
	call	eeprom.read
	andlw	(1<<fMirrorData | 1<<fMirrorNext)
	iorlw	(1<<fHoldTimeout)
	movwf	flags
	return


; EEPROM Read Function
eeprom.read
	banksel	EEADR
	movwf	EEADR
	banksel	EECON1
	ifdef	EEPGD
	bcf	EECON1, EEPGD
	endif
	bsf	EECON1,RD

	banksel	EEDATA
	movfw	EEDATA
	banksel	PORTA
	movwf	eesave_W
	return
	
	;------------------------------------------
save.opmode	clrw
	call	eeprom.set.addr
	movfw	seqMatch
	call	eeprom.write.data

	movlw	0x01
	call	eeprom.set.addr
	movfw	mode
	call	eeprom.write.data

	movlw	0x02
	call	eeprom.set.addr
	movfw	flags
	call	eeprom.write.data

	bcf	flags, fSaveMode	; clear flag

	return

; EEPROM Write Functions
eeprom.set.addr
	banksel	EEADR
	movwf	EEADR
	banksel	PORTA
	return

eeprom.write.data
	banksel	EEDATA
	movwf	EEDATA
	banksel	EECON1
	ifdef	EEPGD
	bcf	EECON1, EEPGD
	endif
	bsf	EECON1,WREN
	movlw	0x55
	movwf	EECON2
	movlw	0xAA
	movwf	EECON2
	bsf	EECON1,WR
	clrwdt
	btfsc	EECON1,WR
	goto	$-2
	banksel	PORTA
	return

;---------------------------------------------------------
