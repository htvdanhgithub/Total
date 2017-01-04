; PWM LED Chaser Interrupt Handler
; rev 1.0.0
              movwf         save_W        ; Preserve W, STATUS and PCLATH
              swapf         STATUS,w
              movwf         save_Status
              movfw         PCLATH
              movwf         save_PCLATH
	clrf	PCLATH
              bank0

	clrwdt		;clear watchdog timer
              movlw         cTIMER        ;load W with timer constant
              addwf         TMR0,F        ;write to Timer 0
              bcf           INTCON,T0IF   ;and clear TimerO int flag

              call          _pwm          ; drive LEDs
              
              decfsz        tick,F        ;decrement ticks
              goto          _exitINT      ;exit Interrupt handler if ticks not 0
              movlw         cTICKS        ;reload tick
              movwf         tick          ;counter
              
              bsf           flags, fTick        ; set tick timeout flag bit
              
              decf          holdTime,F          ; decrement holdtime counter
              skpnz                             ; skip next if not reached zero
              bsf           flags, fHoldTimeout ; set hold timeout flag bit

	
	btfss	flags, fSaveMode
	goto	_exitINT
	
	decfsz	saveModeTimerL,F
	goto	_exitINT
	decfsz	saveModeTimerH,F
	goto	_exitINT
	call	save.opmode



_exitINT    	movfw         save_PCLATH   ;Restore PCLATH
              movwf         PCLATH
              swapf         save_Status,W ;Restore STATUS and W
              movwf         STATUS        
              swapf         save_W,F
              swapf         save_W,W
              retfie                      ;exit from interupt handler