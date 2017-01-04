; ********************************************************************************
; RGB Stand-alone driver Functions include file

; Functions
; --------------------------------------------------------
;
;
;_pwmDrive      drive RGB LEDs with a PWM signal to control brightness
;               code loops continually.
;               Input on GPIO,4 determines whether active drive is high or low
;               The input is only read at power-on / reset.
;
; _seqData      Loads next data block for current sequence
;               resets to start at end of data
;               no parameters. contents of W lost
;
; _advSeq       Advance to next sequence.
;               Set Sequence No counter
;               Reset to first seqence when it reaches end
;               of available sequences.
;               no parameters.
;               return W=1, reset to first sequence
;               teturn W=0, not reset to first sequence
;
;_advResetBase  Initialise sequence data pointer variables
;               no parameters, contents of W lost
;               
;_sleep         If Sequence switch held down for over 1.2S 
;               put PIC to sleep
;               no parameters, PIC resets after return from sleep
;
;_initEEPROM    Initialise EEPROM with valid default values
;               initiate save and wait until it has completed.               
;
;
;_essRun        EERPOM Save State function 
;               set ess variable == 1 to start save
;               ess == 0 save complete / idle               
;               ess == 2 save in progress
;               (this function calls other sub functions)
;
;
;_readEERPOM    Restore saved sequence state from EEPROM
;               no parameters
;               W destroyed
;               (this function calls other sub functions)
;
;------------------------------------------------
; PWM Driver 
; 
;
           

_pwmDriveHi     incfsz          pwmramp,F
    goto            _noRolloverHi
    incf            pwmramp,F
                
    movfw           rpwm
    movwf           rpwmWkg
    incfsz          rpwmWkg,W
    bcf             GPIO,red

    movfw           gpwm
    movwf           gpwmWkg
    incfsz          gpwmWkg,W
    bcf             GPIO,green

    movfw           bpwm
    movwf           bpwmWkg
    incfsz          bpwmWkg,W
    bcf             GPIO,blue
                
    btfsc           INTCON,T0IF
    call            _timerOut

                
_noRolloverHi   incf            rpwmWkg,F
    skpnz
    bsf             GPIO,red

    incf            gpwmWkg,F
    skpnz
    bsf             GPIO,green

    incf            bpwmWkg,F
    skpnz
    bsf             GPIO,blue
                                
    goto            _pwmDriveHi






;----------------------------------------------
; Cycle through single sequence.
;
_seqData        call            _seqLookup      ; read data
    movwf           rate            ; save in rate
    addlw           .1              ; add 1 (test for 255)
    bz              _seqRestart     ; if data was 255 reset seq
    movlw           rate            ; load W with address of rate var
    movwf           FSR             ; write to FSR
                
_seqNxtData     incf            FSR,F           ; increment FSR
    incf            seql,F          ; increment seq pointer low
    skpnz                           ; skip if result != 0
    incf            seqh,f          ; increment seq pointer high
                
    call            _seqLookup      ; read data
    movwf           INDF            ; save via Indirection 
    movlw           bnew            ; load W with address of blue new var
    xorwf           FSR,W           ; test if FSR == address of blue new var
    bnz             _seqNxtData     ; if not read next data byte
    incf            seql,F          ; otherwise increment seq data pointer
    skpnz                           ; ready for next
    incf            seqh,F          ; call to get seq data
                
    return


_seqRestart     movfw           sbl             ; get sequence base low
    movwf           seql            ; save to current sequence low
    movfw           sbh             ; get sequence base high
    movwf           seqh            ; save to current seqence high
    goto            _seqData        ; load start of sequence
                
_seqLookup      movfw           seqh            ; data table lookup
    movwf           PCLATH
    movfw           seql
    movwf           PCL
                
;----------------------------------------------
; Advance to next sequence (cycle)
;
_advSeq         call            _advLookup      
    addlw           0x01
    bz              _advEnd
    movlw           0x05
    addwf           sbl,f
    skpnc
    incf            sbh,f
    goto            _advSeq
                

_advEnd         incf            currentSeqNo,F
    incf            sbl,f
    skpnz
    incf            sbh,f
    call            _advLookup
    addlw           0x01
    skpnz           
    goto            _advResetBase
    movfw           sbl
    movwf           seql
    movfw           sbh
    movwf           seqh
    clrw                            ; return with W = 0
    return
                
                                
_advResetBase   clrf            currentSeqNo
    movlw           HIGH _base
    movwf           sbh
    movwf           seqh
    movlw           LOW _base
    movwf           sbl
    movwf           seql
    iorlw           0xFF            ; return with W != 0
    return

                ;-------------------------
                ; lookup
_advLookup      movfw           sbh
    movwf           PCLATH
    movfw           sbl
    movwf           PCL

;-------------------------------------------
; Fade Direction
; 

_fadeDir        movfw           hold            ; Set hold timer
    movwf           holdTimerHi
    movfw           rate            ; Set fade rate timer
    movwf           fadeTimer       
    bnz             _calcFade       ; if fade rate == 0
    movfw           rnew            ; No fade so load
    movwf           rpwm            ; pwm variables
    movfw           gnew            ; with new data
    movwf           gpwm            ; to get instant
    movfw           bnew            ; colour change
    movwf           bpwm            ; ...
    clrf            fadeflag        ; clear fade flag so code goes straight to hold
    return                          ; return
                

;-------------------------------------------
; Calculate the difference between current and new
; PWM value for each colour. Set fade direction to +/-1
                
                
_calcFade       movlw           (1<<red | 1<<green | 1<<blue)
    movwf           fadeflag        ; preset fade flag
    movlw           0x01            ; preset fade direction to +1 for each colour
    movwf           rdir
    movwf           gdir
    movwf           bdir
                
    movfw           rpwm
    subwf           rnew,W          ; subtract current from new (W = current - new)
    bc              _rabs           ; branch if C=1  (current > new)
    decf            rdir,F          ; rdir is 1, decrement twice
    decf            rdir,F          ; to make rdir -1.
    sublw           0x00            ; sub W from 0 to make W positive
_rabs           movwf           Rdif            ; save difference between current and new


    movfw           gpwm
    subwf           gnew,W          ; subtract current from new (W = current - new)
    bc              _gabs           ; branch if C=1  (current > new)
    decf            gdir,F          ; rdir is 1, decrement twice
    decf            gdir,F          ; to make rdir -1.
    sublw           0x00            ; sub W from 0 to make W positive
_gabs           movwf           Gdif            ; save difference between current and new

    movfw           bpwm
    subwf           bnew,W          ; subtract current from new (W = current - new)
    bc              _babs           ; branch if C=1  (current > new)
    decf            bdir,F          ; rdir is 1, decrement twice
    decf            bdir,F          ; to make rdir -1.
    sublw           0x00            ; sub W from 0 to make W positive
_babs           movwf           Bdif            ; save difference between current and new


;-------------------------------------------
; Find largest difference between current and new RGB values
;               
                
_calcLargest    movfw           Rdif
    subwf           Gdif,W
    bc              _chkGB
                
    movfw           Rdif
    subwf           Bdif,W
    movfw           Bdif
    bc              _done
    movfw           Rdif
    goto            _done
                
_chkGB          movfw           Gdif
    subwf           Bdif,W
    movfw           Bdif
    skpc            
    movfw           Gdif

_done           sublw           0x00
    movwf           CntBase
    movwf           Rcnt
    movwf           Gcnt
    movwf           Bcnt
                
    return
                


;-------------------------------------------
; Put PIC to sleep
; 
_sleep          movlw           .1
    movwf           ess             ; force EEPROM save to state to initialise
    call            _initLoop       ; save to EERPROM
    movfw	driveLevel
    movwf	GPIO	; turn off all outputs
                
_waitSwRelSleep btfss           GPIO,seqSw      ; test seqSw
    goto            _waitSwRelSleep ; wait for it to be released
    movlw           .15
    call            _swDelay
                                
    movfw           GPIO            ; read GPIO port to clear Int-on-change 
    bcf             INTCON,GPIF     ; clear int-on-change flag
    sleep                           ; put PIC to sleep
    nop

    movlw           .90             ; approx. 1 second delay
    call            _swDelay        ; wait after wake up
    btfsc           GPIO,seqSw      ; test switch to see if it is still down
    goto            _waitSwRelSleep ; if not go back to sleep
_waitSwRelWake  btfss           GPIO,seqSw      ; wait for sequence switch to be 
    goto            _waitSwRelWake  ; released before continuing
    goto            _startup        ; After wake-up run startup code
                                                ; as if it was a power-on startup


_swDelay        clrf            TMR0            ; delay to debounce the switch
    bcf             INTCON,T0IF     ; 
_waitSleep      btfss           INTCON,T0IF     ; 
    goto            _waitSleep
    addlw           -.1
    skpz
    goto            _swDelay
    return

; *********************************
; EEPROM write
; call with W reg containg sequence # to save
;
_eeWrite        setbank1
    movwf           EEDATA          ; save W into EEDATA
    incf            EEADR,F
    bsf             EECON1,WREN     ; initiate EEPROM write sequence
    movlw           0x55
    movwf           EECON2
    movlw           0xAA
    movwf           EECON2
    bsf             EECON1,WR
                setbank0
    return                          ; return
              
; *********************************
; EEPROM read
; returns with saved sequence # in W reg

_eeRead         setbank1
    incf            EEADR,F
    bsf             EECON1,RD       ; initiate EEPROM read
    movf            EEDATA,W        ; load EEPROM data into W
	setbank0
    return                          ; return   



; *********************************
; Save state to EEPROM 
;
_initEEPROM     incf            ess,F
    clrf            savedSeqNo
    clrf            currentSeqNo
    clrf            freeze
    clrf            rpwm
    clrf            gpwm            
    clrf            bpwm
_initLoop       call            _essRun
    movf            ess,F
    bnz             _initLoop
    return


_essRun         movfw           ess             ; load state into W reg
    skpnz                           ; skip next if ess != 0
    return                          ; return (ess idle state)
    addlw           -.1             ; test if state == 1
    bz              _essInit        ; run _essInit function if state == 1
                                                ; else drop through and run _essSave
                ; ess 2
                ; 
_essSave        setbank1
    movfw           EECON1          ; read EECON1 register into W
                setbank0
    andlw           (1<<WR)         ; test EEPROM write flag
    skpz                            ; skip if write complete
    return                          ; return if not
    movfw           INDF            ; get data to write using indirect address

    call            _eeWrite        ; start write
    incf            FSR,F           ; increment indirect address pointer
    movfw           FSR             ; 
    xorlw           (base+.6)       ; test if all data written
    skpnz                           ; skip next if not complete
    clrf            ess             ; else reset state variable to 0 (idle)
    return                          ; and return


                ; ess 1
                ; copy variables to save into buffer area
_essInit        movfw           currentSeqNo    ; get variable to save
    movwf           base            ; write to base address
    movwf           base+.5         ; base+5 holds checksum
    movfw           rpwm            ; get next variable to save
    movwf           base+.1         ; write to base+1
    addwf           base+.5,F       ; add to checksum
    movfw           gpwm            ; et al.
    movwf           base+.2
    addwf           base+.5,F       ; add to checksum        
    movfw           bpwm
    movwf           base+.3
    addwf           base+.5,F       ; add to checksum
    movfw           freeze
    movwf           base+.4
    addwf           base+.5,W       ; add to checksum
    sublw           0x00
    movwf           base+.5
                                
    movlw           base            ; load W with address of base
    movwf           FSR             ; write to FSR indirect register
                setbank1
    clrf            EEADR           ; set EEADR to 0
                setbank0                
    incf            ess,F           ; set to next state
    return

; *********************************
; Swap FSR with FSRsave;

_swapFSR        movfw           FSR
    xorwf           FSRsave,F
    xorwf           FSRsave,W
    xorwf           FSRsave,F
    movwf           FSR
    return          


; *********************************
; Restore state from EEPROM 
;
_readEEPROM     setbank1
    btfsc           EECON1,WR
    goto            $-1
    clrf            EEADR
    call            _eeRead
    movwf           savedSeqNo
    movwf           saveCnt
                
    call            _eeRead
    movwf           rpwm
    addwf           saveCnt,F
                
    call            _eeRead
    movwf           gpwm
    addwf           saveCnt,F

    call            _eeRead
    movwf           bpwm
    addwf           saveCnt,F

    call            _eeRead
    movwf           freeze
    addwf           saveCnt,F

    call            _eeRead
    addwf           saveCnt,W       ; returns with checksum in W
    return