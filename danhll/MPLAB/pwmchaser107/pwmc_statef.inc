; PWM LED Chaser Main state function code block
; Use with pwmc_main103.asm only


_idleState    call          _runState     ; runs state code function
              btfss         flags, fTick  ; test for timer tick flags set
              goto          _idleState    ; idle if flag clear
              bcf           flags, fTick  ; reset timer tick flag     


              ; if switch held down and count reaches .128, we set State variable to 6 (run/setup state)
              ; otherwise we wait until switch is released, if it was held down long enough
              ; to debounce the switch but not long enough to enter run/setup state we
              ; set the fSwitch flag on release and let current state function handle switch
              
              btfss         PORTA, switch ; test if Switch is down
              goto          _swDown       ; do switch down code if it was

              incf          swTimer,W     ; test if swTimer == 255 by adding 1, result in W
              skpnz                       ; skip next if result not 0 ( 255 + 1 = 0)
              goto          _resetSwTimer ; else we've just returned from a long hold so don't do debounce.

                                          ; value in W is swTimer + 1 from incf above
              addlw         -.4           ; add 251 to W
              skpnc                       ; skip next if if W + 251 < 256 ( carry left clear)
              bsf           flags, fSwitch ; otherwise set fSwitch flag

_resetSwTimer clrf          swTimer       ; reset switch timer
              goto          _idleState    ; and run idle loop


_swDown       
              incf          swTimer,W     ; increment timer while switch down
              skpnz                       ; skip if timer increment doesn't rollover to 0
              goto          _idleState    ; else hold timer at 255 until switch released
              movwf         swTimer       ; load current value into W
              xorlw         .128          ; this test will set/clear Z flag in STATUS register
              movlw         .6            ; load W with state 6 (won't affect STATUS register)
              skpnz                       ; skip if the XORLW .128 wasn't zero.
              movwf         state         ; else set state to do long switch
              goto          _idleState


; 

_runState     ; run state selector code. Must reside in page 0 of program memory
              clrf          PCLATH        ; reset PCLATH (expects code in page 0)
              movfw         state         ; load state variable into W
              addwf         PCL,F         ; add W to current PCL which jumps to one of the
                                          ; goto's in the list below to select the state function.
              goto          _S00          ; 0  
              goto          _S01          ; 1  
              goto          _S02          ; 2
              goto          _S03          ; 3
              goto          _S04          ; 4
              goto          _S05          ; 5
              goto          _S06          ; 6
              goto          _S07          ; 7              
              
; Each state code function will either leave the state varaible unchanged or modify it before exiting
; to control the operation of the sequencer.  

; State 0
; 
_S00          incf          state,F                     ; set State == 1
              movfw         seqMatch
              call          _countSeqIn                 ; find address of first sequence
              
              bcf           flags, fMirrorData          ; clear mirror data flag
              bcf           flags, fMirrorNext          ; clear mirror next flag
              call          _setIndex                   ; set sequence base address and repeat count
	btfsc         mode,modeRan                ; test if we're in Random mode
              goto          _S00rndMir                  ; do random mirror

              btfsc         repeatCount, fMirrorData
              bsf           flags, fMirrorNext
              call          _Lookup                     ; 
   
              return

_S00rndMir    btfss         repeatCount, fMirrorData    ; is canMirror bit set for this sequence?
              return                                    ; if not we're done
              call          _randNum                    ; get random number (use carry flag on return)
              skpc                                      ; skip if carry flag clear
              bsf           flags,fMirrorData           ; and set MirrorData flag if it is set
              call          _Lookup
              return


; State 1
_S01
              ; if switch pressed skip to next sequence.  This happens in all auto/random and manual modes
              btfss         flags, fSwitch              ; test switch flag
              goto          _S01auto                    ; do _S01auto if switch up
              bcf           flags, fSwitch              ; clear switch flag
              movlw         .3                          ; set State to 3
              movwf          state

	movlw	cSAVETIME
	movwf	saveModeTimerH
	clrf	saveModeTimerL
	bsf	flags, fSaveMode

              return

_S01auto      btfss         flags, fHoldTimeout         ; test hold timeout flag
              return        
              movfw         repeatCount                 ; read repeat count into W reg
              andlw         b'00011111'                 ; mask off bits in repeatCount
              skpz                                      ; skip next if repeatCount == 0
              goto          _Lookup                     ; else read next entry of current sequence
                                                        ; the 'goto _Lookup' means we'll use its return to get back to the call
              incf          state,F                     ; change to next state
              return

; State 2     
_S02          incf          state,F
              btfss         mode, modeMan               ; test and skip next if mode is manual
              return
              call          _setIndex                   ; set sequence base address and repeat count
              call          _Lookup       
              movlw         .1                          ; Set State back to 1
              movwf         state
              return        


; State 3
_S03          incf          state,F
              btfsc         mode, modeRan               ; don't check mirror state if Random mode on
              return
              btfss         flags, fMirrorNext          ; is 'canMirror' flag set for this sequence?
              return
              call          _setIndex                   ; reset sequence base addess and repeat count
              bcf           flags,fMirrorNext           ; clear fMirrorNext'flag 
              bsf           flags,fMirrorData           ; set the MirrorData flag table data gets mirrored
              movlw         .1                          ; Set State back to 1
              movwf         state
              return



; State 4
_S04          clrf          state                       ; Set next State to 0
              btfsc         mode,modeRan                ; test if Random mode
	goto          _getRandSeq
              incf          seqMatch,F                  ; increment sequence number pointer
              movfw         seqMatch                    ; load seqMatch into W
              xorwf         seqTotal,W                  ; test to see if this is the highest sequence 
              skpnz                                     ; skip next if not
              clrf          seqMatch                    ; else reset to select first available sequence
              return

_getRandSeq   call          _randNum
              andwf         RandMask,W                  ; mask off unwanted bits, result in W
              movwf         seqMatch                    ; save W to SeqMatch
              movf          seqTotal,W                  ; load W with SeqTotal
              subwf         seqMatch,W                  ; W = SeqMatch - SeqTotal
              skpnc                                     ; if SeqMatch < SeqTotal we're done
              goto          _getRandSeq                 ; else try another random number
               
              return
                 

; State 5
_S05          ; setup mode state
              ; Remain in this state until the Switch handler code detects a long switch press
              ; and changes state for us.
              clrf          loReload                    ; clear pwm reload counter low
	movfw	mode
	movwf	hiReload              

              btfss         flags, fSwitch              ; test if switch flag set
              return                                    ; do nothing if it is clear

              bcf           flags, fSwitch              ; clear switch flag
              ; 76543210   3 = Sleep, 2 = Man, 1 = AutoRand, 0 = AutoSeq
                            
	clrc                               ; make sure carry flag is clear
	movlw	1<<modeSeq           ; load W with first mode bit set
	
	; Mode 3  puts the PIC into a low power sleep mode, where it waits for the switch
	; to be pressed for about 2-3 seconds when it will leave sleep mode and reset/restart.
	; Not enabled in the web release of the code but if you swap the commented/uncommented
	; btfss instructions around below it will enable it.
	;
	;btfss	mode, modeSleep       ; sleep mode not in webrelease
	btfss	mode, modeMan        ; If this is the current mode then
	                                   ; skip the rotate that follows                                      
	rlf	mode,W               ; shift bit to select next mode, result in W
	movwf	mode                 ; put W back in mode register

                                                                                                               
              return


; State 6
; Long Switch test
_S06

              movlw         .7                          ; preload W with state 7
              btfss         flags, fsetupRun            ; skip if we're in run mode
              movlw         .5                          ; reload W with state 5
              movwf         state                       ; set state to either run or setup
              bcf           flags, fSwitch              ; clear switch flag
              movlw         1<<fsetupRun                
              xorwf         flags,F                     ; toggle fsetupRun mode flag

              movlw         .255                        ; load Wreg with .255
              movwf         swTimer                     ; Wreg to swTimer var 

	btfss	mode, modeSleep
	return                                    ; return

; sleep mode, PIC enters sleep state and is woken by the watchdog timer when it 
; tests the switch input.  If switch has been held down for about 2 seconds the PIC
; will restart the chaser by jumping to the reset vector, otherwise it goes back to sleep
; This code is fully functional but not enabled in the web release version

	bcf	INTCON, T0IE		; disable Timer 0 interrupts
	bcf	INTCON, T0IF		; clear Timer 0 interrupt flag
	bcf	INTCON, GIE		; disable global interrupts

	clrwdt
	clrf	TMR0
	bank1
	movlw	b'00001111'
	movwf	OPTION_REG
	bank0
	clrf	PORTB		; turn off all LEDs outputs
_snooze	clrf	swTimer
_sleep	sleep
	clrwdt
	btfsc	PORTA, switch
	goto	_snooze
	incf	swTimer,F
	movfw	swTimer
	xorlw	.2
	bnz	_sleep
	goto	START
	

              
; State 7
_S07          ; return from setup to run mode
              clrf          loReload                    ; clear pwm reload counters (looks better if we do)
              clrf          hiReload                    ; 
              clrf          state                       ; restart sequence by entering state 0

	movlw	cSAVETIME
	movwf	saveModeTimerH
	clrf	saveModeTimerL
	bsf	flags, fSaveMode

              return        