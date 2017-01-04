; PWM LED Chaser
; MACRO definitions for creating Sequence Data tables
;
; *****************************************************************
; This code expects you to enter the sequence data correctly.
; If you miss fields, enter incorrect values or generally don't
; get the format correct, the code will crash or behave irraticaly.
; *****************************************************************
;

              radix decimal
              ; set number base to decimal so it's easier to work with


; -----------------------------------------------------------------
; Example:
;
;
;              control 0,2                 ; no mirror, repeat twice
;
;              hold 50                     ; hold for 50 x 10mS = 0.5S
;              sdat 0,0,0,0,0,0,0,0        ; all LEDs off
;              hold 50                     ; hold for 50 x 10mS = 0.5S
;              sdat 1,1,1,1,1,1,1,1        ; all LEDs dim brightness
;              hold 75                     ; hold for 75 x 10mS = 0.75S
;              sdat 2,2,2,2,2,2,2,2        ; all LEDs mid brightness
;              hold 75                     ; hold for 75 x 10mS = 0.75S
;              sdat 3,3,3,3,3,3,3,3        ; all LEDs full brightness
;
;              seqend                      ; mark end of this sequence


; Each sequence starts with the control parameter.
;
; This specifies the number of times to repeat the sequence and whether the 
; sequence is suitable for mirroring.
;
;   control  Can_Mirror, Repeat count
;            True  if Can_Mirror = 1
;            False if Can_Mirror = 0
;            Repeat_Count >=1, 31=< 
;
; Repeat count.
; Sequence will repeat this many times before moving to the next sequence
; 
; Mirroring
; Asymetric patterns, for example a sequence that moves a dot from left to right are suitable for mirroring
; since the same data when mirrored creates a different pattern.  This effecitively gives two different 
; sequence patterns without requiring two sets of data.
; Symetrical patterns when mirrored will appear exactly the same, there is no reason to mirror them, but
; it doesn't care if you do.
;
control       macro Mmirror, Mtimes
              if (1>Mtimes) || (Mtimes>31)
               error "Repeat count in sequence data is out of range. Must be between 1 and 31."    
              endif
              retlw  (1&&Mmirror)<<6 | (Mtimes & .31)
              endm

; Each line of seqence data is preceded by a hold time parameter
; This specifies how long to hold the pattern before moving to the next
; line of data in the sequence. 

              ; hold hold_value
              ;    1<= hold_value <= 254
              ; hold time = hold_value * 10mS
              ; e.g. hold 15 holds for 150mS

hold  macro Mseqhold
              if (1>Mseqhold) || (Mseqhold>254)
               error "Hold value in sequence data is out of range. Must be between 1 and 254."    
              endif
              retlw  Mseqhold
              endm

; Sequence Data pattern. Each of the 8 LEDs can be set to one of 4 brightness levels
; 0 = off
; 1 = dim
; 2 = mid
; 3 = full
;
; The pattern is specified as 8 comma seperated fields representing LEDs 7-0
; LED  7  6  5  4  3  2  1  0
; sdat n, n, n, n, n, n, n, n
; e.g. sdat 0, 1, 2, 3, 3, 2, 1, 0


sdat    macro Mb7,Mb6,Mb5,Mb4,Mb3,Mb2,Mb1,Mb0
              retlw  (1&&(Mb7&1))<<7 | (1&&(Mb6&1))<<6 | (1&&(Mb5&1))<<5 | (1&&(Mb4&1))<<4 | (1&&(Mb3&1))<<3 | (1&&(Mb2&1))<<2 | (1&&(Mb1&1))<<1 | (1&&(Mb0&1))<<0
              retlw  (1&&(Mb7&2))<<7 | (1&&(Mb6&2))<<6 | (1&&(Mb5&2))<<5 | (1&&(Mb4&2))<<4 | (1&&(Mb3&2))<<3 | (1&&(Mb2&2))<<2 | (1&&(Mb1&2))<<1 | (1&&(Mb0&2))<<0
             endm


; The end of a sequence is marked with the seqend macro
; This must always be present, if it's missing the code will crash.
seqend  macro
              retlw  .255
              endm
              
; Tip:
; If you put two 'seqend' at the end of a sequence it will treat it as the end of
; all sequences.  Any sequence data after it will be ignored by the program. This can
; be handy when testing new sequences. Put the new sequence at the top of the sequence
; data file and add two 'seqend', then it will only run that sequence.
; 


