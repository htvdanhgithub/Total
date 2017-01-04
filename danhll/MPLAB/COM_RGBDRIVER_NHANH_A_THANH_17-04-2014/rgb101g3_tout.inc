;--------------------------------------------------------
; 5mS Time Out
; This code runs approximately every 5mS
; The PWM code calls it at the end of each PWM cycle if TMR0 has
; overflowed.  Because the PWM code takes approximatley 4mS to run
; we add the current TMR0 contents to the cTIMER constant so that
; over a number of passes the average time-out is 5mS
; This method is accurate enough to get predicatable delays
; needed for this application.  However because the write to the timer
; clears the prescaler at some random point, it isn't accurate over
; many seconds or minutes.
 

_timerOut       movfw           TMR0            ; load current TMR0 into W
                addlw           cTIMER          ; add TIMER constant to W
                movwf           TMR0            ; write back to TMR0
                bcf             INTCON,T0IF     ; clear Timer 0 Interrupt flag

;-----------------------------------------------------
; EEPROM save counter
                                
                call            _swapFSR
                call            _essRun
                call            _swapFSR
                
                movf            saveCnt,F
                bz              _switchCheck
                decfsz          saveCntPS,F
                goto            _switchCheck
                decfsz          saveCnt,F
                goto            _switchCheck
                movlw           .1
                movwf           ess
;-----------------------------------------------------
; Sequence Switch Check

_switchCheck    goto            _fadeState    ; Danh Hoang: disable SeqSW
                movf            seqSwDblClk,F
                skpz
                decf            seqSwDblClk,F   

                btfsc           GPIO,seqSw
                goto            _seqSwUp        
                                
_seqSwDown      incf            seqSwCnt,F      ; increment seqSwCnt counter variable
;Danh Hoang: turn off sleep mode
;                skpnz                           ; if result == 0, counter has wrapped round
;                goto            _sleep          ; so goto sleep
                goto            _fadeState

_seqSwUp        movlw           -.4             ; 20mS
                addwf           seqSwCnt,W      ; was switch down for over 20mS
                bc              _swShort
                clrf            seqSwCnt
                goto            _fadeState
                

_swShort        movf            seqSwDblClk,F
;Danh Hoang: turn off double click mode
;                bnz             _swDoubleClick
                
                clrf            seqSwCnt
                movlw           0x01
                xorwf           freeze,F
                movlw           .100
                movwf           seqSwDblClk
                movlw           cSAVETIMER      ; set save to EEPROM timer
                movwf           saveCnt         ; for delay after last sequence change.
                goto            _fadeState


_swDoubleClick  call            _advSeq         ; advance to next sequence
                call            _seqData        ; get first set of sequence data
                clrf            rpwm            ; reset current Red pwm to 0
                clrf            gpwm            ; reset current Greeb pwm to 0
                clrf            bpwm            ; reset current Blue pwm to 0
                call            _fadeDir        ; set fade direction
                movlw           cHOLDPRESCALER  ; reset hold time prescaler
                movwf           holdTimerPS
                clrf            seqSwCnt
                movlw           cSAVETIMER      ; set save to EEPROM timer
                movwf           saveCnt         ; for delay after last sequence change.
                clrf            seqSwDblClk
                clrf            freeze

                                

;-----------------------------------------------------
; fade / hold state function select
                
_fadeState      btfsc           freeze,0        
                return

                movf            fadeflag,F
                bz              _holding
;------------------------------------------------------
; fade          
                
_fading         decfsz          fadeTimer,F
                return
                movfw           rate
                movwf           fadeTimer

;----------------------------------------
; Fade stepper
;

_Rfade          movfw           rnew
                xorwf           rpwm,W
                bnz             $+3
                bcf             fadeflag,red
                goto            _Gfade

                movfw           Rdif
                addwf           Rcnt,F
                skpc            
                goto            _Gfade
                movfw           CntBase
                addwf           Rcnt,F
                movfw           rdir
                addwf           rpwm,F
                
_Gfade          movfw           gnew
                xorwf           gpwm,W
                bnz             $+3
                bcf             fadeflag,green
                goto            _Bfade

                movfw           Gdif
                addwf           Gcnt,F
                skpc            
                goto            _Bfade
                movfw           CntBase
                addwf           Gcnt,F
                movfw           gdir
                addwf           gpwm,F

_Bfade          movfw           bnew
                xorwf           bpwm,W
                bnz             $+3
                bcf             fadeflag,blue
                return
                
                movfw           Bdif
                addwf           Bcnt,F
                skpc            
                return          
                movfw           CntBase
                addwf           Bcnt,F
                movfw           bdir
                addwf           bpwm,F
                return




;------------------------------------------------------
; Hold pwm values timer         
                
_holding        movf            holdTimerHi,F   ; test holdTimerHi == 0
                bz              _holdSeqNext    ; no hold if it was 0
                
                decfsz          holdTimerPS,F
                return
                movlw           cHOLDPRESCALER
                movwf           holdTimerPS
                decfsz          holdTimerHi,F
                return
_holdSeqNext    call            _seqData
                call            _fadeDir
                
                return

