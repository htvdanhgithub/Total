; ********************************************************************************
; RGB101G3 code for use with the RGB LED Moodlight PCB 101
; Core code is based on Generic RGB Standalone LED driver version 3.0.3 (28/09/2008)
;
; rgb101g3 for use with circuit version 101D
; http://picprojecs.org.uk/projects/rgb101/
;
; Pete Griffiths (c) 2010
; info@picprojects.org.uk
; Written and assembled using MPLAB v8.56
;
; -----------------------------------------------------------------------------------



; -----------------------------------------------------------------------------------
; Code to fade between colours is completely rewritten to use variable rate of change
; so that all three LEDs arrive at their new levels simultaneously.
;
; This code will run on 12F629 / 12F675 and 12F683. Select the desired processor
; from the Configure - Select Device menu option in MPLAB IDE, then use the
; Project - Quickbuild option to create the .HEX output file.
; 
; Look for errors during assembly. In particular errors in the SequenceData.inc
; file that indicate either a missing comma in the data, or more data than the 
; chosen PIC has available program memory.
; 
; Be carefull to enter the data in the SequenceData.inc file correctly.  The program
; is only smart enough to work out where your sequences start and finish if you enter
; it in the correct format.  Errors in the data may cause the code to crash.
;
; ********************************************************************************
; Note: For 12F629 and 12F675
; All timings are based on the internal 4Mhz PIC oscillator.  The OSCCAL value is read
; from program memory at 0x3FF and written to the OSCAL register.  This value must be
; present and correct. 
;
;             -=# IF IT IS MISSING THE CODE WILL NOT RUN CORRECTLY #=-
; See http://picprojects.org.uk/projects/recal/ if you need to recalibrate the PIC
;
; This does not apply to 12F683 as it doesn't use this method to calibrate the oscillator
;
; ********************************************************************************
; Pinout connections 
;                            ___ ___
;                       Vdd -|1 ^ 8|- Vss
;      Sequence Change Sw1  -|2   7|- red output
;              blue output  -|3   6|- green output
;  MCLR. tie to Vdd via 1K  -|4   5|- not used
;                           ¯¯¯¯¯¯¯
;  Ensure that MCLR is pulled to Vdd using 1K resistor for 12F629/675. 
;
; Sw1 performs multiple functions.
;  1. single press to hold / run displayed colour sequence
;  2. double press to step to next sequence
;  3. press and hold >1.5 seconds to enter sleep mode
;     in sleep mode press, hold for >1.5 seconds then release to wake from sleep
;
;  note :double press is like double clicking a mouse button when using a PC.
;
;
; ********************************************************************************
; Revision information
; rgb101g3_main.asm version 3.0.0
;
;  First release
;  This code is based on genrgbsa version 3.0.3 code with modification for use
;  with the revised I/O pin use on PCB Revsision 101D
;
;  
;
; ********************************************************************************

  IFDEF  __12F683
                #include "p12f683.inc"
                #define ADCpresent
  ENDIF

          
  IFDEF  __12F675
                #include "p12f675.inc"
                #define ADCpresent
  ENDIF

  IFDEF  __12F629
                #include "p12f629.inc"
                
  ENDIF

  IFDEF __12F683                
     __CONFIG       _CP_ON & _WDT_OFF & _BOD_OFF &_PWRTE_ON & _INTRC_OSC_NOCLKOUT & _MCLRE_ON & _CPD_ON
  ELSE
     __CONFIG       _CP_ON & _WDT_OFF & _BODEN_OFF & _PWRTE_ON & _INTRC_OSC_NOCLKOUT & _MCLRE_ON & _CPD_ON
  ENDIF
  
                errorlevel -302 ; suppress banksel warning messages
       
; Program data memory variables
; --------------------------------------------
;          
                cblock          0x20 
                                 
                 rdir           ; red fade direction
	         gdir           ; green fade direction
                 bdir           ; blue fade direction
                 Rdif           ; absolute difference between red now and next
                 Gdif           ; absolute difference between green now and next
                 Bdif           ; absolute difference between blue now and next
                 Rcnt           ; fade step counter red
                 Gcnt           ; fade step counter green
                 Bcnt           ; fade step counter blue
                 CntBase        ; fade base count holding variable
                 rpwmWkg        ; temp working variable for PWM
                 gpwmWkg        ; temp working variable for PWM
                 bpwmWkg        ; temp working variable for PWM
                 fadeflag       ; fade complete flag variable
                 pwmramp        ; pwm ramp counter
                 driveLevel     ; select drive level
              	 sbl            ; Sequence Base Low
                 sbh            ; Sequence Base High
                 seql           ; Current Sequence data pointer Low
                 seqh           ; Current Sequence data pointer High
                 currentSeqNo   ; Current Sequence No
                 highSeqNo      ; Highest Sequence No
                 rate           ; Fade rate
                 hold           ; Sequence hold time
                 rnew           ; red data
                 gnew           ; green data
                 bnew           ; blue data
                 seqSwCnt       ; sequence switch counter
                 seqSwDblClk    ; seqence switch double click counter
                 saveCntPS      ; save to EERPOM counter prescaler
                 fadeTimer      ; fade rate timer counter
                 holdTimerPS    ; hold timer prescaler
                 holdTimerHi    ; hold timer counter

	 base:6         ; eeprom save data buffer
      	 saveCnt        ; save to EEPROM counter 
                 savedSeqNo     ; saved Sequence No read from EEPROM
                 freeze         ; SW1 run/freeze flag
                 ess            ; eeprom save state flag                                 
                 FSRsave        ; used to save FSR reg which is usedby two functions.
                 rpwm           ; red pwm level
                 gpwm           ; green pwm level
                 bpwm           ; blue pwm level

	endc



                
;----------------------------------------------------------
; program Constants - DO NOT change them
cTIMER          equ             .179            ; Timer 0 constant 
                                                ; for 5mS timer tick

cHOLDPRESCALER  equ             .10             ; rgb hold counter prescaler
                                                ; 5mS x Prescaler x holdtime
                                                                
cSAVETIMER      equ             .8              ; time after last seq switch change
                                                ; before saving to EEPROM
                                                ; in increments of 1.28S

;----------------------------------------------------------
; GPIO port variables - DO NOT change them
red             equ             0               ;out
green           equ             1               ;out
blue            equ             4               ;out
gpio3           equ             3               ;in (only)
auxIn           equ             2               ;in
seqSw           equ             5               ;in
                
;----------------------------------------------------------
;
;
; Bank Select macro instructions
#define         setbank0        bcf             STATUS,RP0      ; Sel Bank 0
#define         setbank1        bsf             STATUS,RP0      ; Sel Bank 1
                
                org 0x000
                
                include         rgb101g3_start.inc
                include         rgb101g3_func.inc
                include         rgb101g3_tout.inc
                radix decimal
_base
                include         SequenceData.inc

;               ------------------------------------------------------------------------
                ; Embed code revision into program memory
                ;dt "rgb101g3_main.asm 14/09/2010 R3.0.3"  
                ; dt "(c) Pete Griffiths 2006-2010 "
                ;dt "info@picprojects.org.uk"
;               ------------------------------------------------------------------------
                
                ;fill 00, 0x3FF-$
                
                end

