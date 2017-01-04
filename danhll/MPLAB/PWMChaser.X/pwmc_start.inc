; PWM LED Chaser Reset and initialisation code block
; Use with pwmc_main103.asm only

START	clrwdt
              clrf          PORTB


              ifdef CMCON
	 ifndef __16F88
                movlw        b'00000111'                 ; disable comparators by setting CM2:CM0 == 111
                movwf        CMCON                       ; See 16F628A datasheet section 10.0
               endif 
	endif
              
              bank1                                     ; set to register bank 1
                                                        ; this is a pseudo instruction defined on earlier
     	ifdef OSCCON
	movlw	b'01100010'	; set OSCCON for internal RC oscillator
	movwf	OSCCON	; running at 4Mhz
              endif

	ifdef ANSEL	; 16F88
	 clrf	ANSEL	; Set I/O ports for digital mode
	endif

              movlw         1<<switch                   ; set PORTA as output except for switch input
              movwf         TRISA
              clrf          TRISB                       ; set PORTB as output

              movlw         b'00000000'   ;setup option register
              ;               ||||||||---- PS0 - Timer 0: Prescalar 1:256
              ;               |||||||----- PS1
              ;               ||||||------ PS2
              ;               |||||------- PSA -  Assign prescaler to Timer0
              ;               ||||-------- TOSE - LtoH edge
              ;               |||--------- TOCS - Timer0 uses IntClk
              ;               ||---------- INTEDG - falling edge RB0
              ;               |----------- RBPU - pull-ups enabled
              movwf         OPTION_REG

              
              bank0                                     ; set to register bank 0
                                                        ; this is a pseudo instruction defined on earlier

	clrf	PORTA	; set all unused outputs on PORTA to 0

              ; Initialise all GPR memory used by variables to 0
              ; This code block is very important.  A number of functionns expect
              ; variables to be zet to zero on first use.  
              movlw         firstGPR      
              movwf         FSR
_clearGPR     movlw         lastGPR
              clrf          INDF
              incf          FSR,F
              xorwf         FSR,W
              skpz
              goto          _clearGPR
              
              movlw         cTIMER        ; load W with timer constant
              movwf         TMR0          ; preset timer
              movlw         cTICKS
              movwf         tick          ; preset ticks

              
              ; find the number of sequences in the sequence data
              ; since this data is user defined we don't know how many there are.
              movlw         .255
              call          _countSeqIn   ; find total individual sequences in data
              
              ; build a mask to AND the random number against so that the MSB of the mask
              ; is the same as the MSB of the highest sequence number. With all lower bits
              ; in the mask set, we can take 8 bit random number and mask off bits higher
              ; than the MSB of the highest sequence value which means random numbers are
              ; pre-conditioned to a similar range to the number of sequences.  
              ; Since the sequences are user defined we have to calculate the mask rather
              ; than using a predefined constant.

_buildMask    decf          seqTotal,W       ; 
              movwf         save_W           ; use save_W variable as temporary working var
              clrf          RandMask
              movlw         .8              
_loopMask     rlf           save_W,F
              movf          RandMask,F
              skpz
              setc
              rlf           RandMask,F
              addlw         -.1
              bnz          _loopMask
              
              clrf          seqMatch      ; make sure this is clear before entering state code

              movlw         .31           ; initialise PWM ramp variable
              movwf         pwm           ; cosmetic really, LEDs will flash on power-up
                                          ; unless we set this here.
              
              ; *************************************************************************              
              ; initialise mode control flags
              ; Code will start in auto-sequential mode 
              ; If you want code to startup in a different mode, change flags here
              ;

	call	restore.opmode
	movlw	.1
	movwf	state
   
              ; 
              ; *************************************************************************

              bcf           INTCON, T0IF  ; clear TimerO int flag
              bsf           INTCON, T0IE  ; enable TMR0 interrupt
              bsf           INTCON, GIE   ; enable Global interrupts

              goto          _idleState    ; start main state function code