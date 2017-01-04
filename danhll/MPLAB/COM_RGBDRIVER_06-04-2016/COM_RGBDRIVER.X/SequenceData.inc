;

;	Sequence Data Format
; --------------------
;	fade_rate, hold_time, red, green, blue (all values in decimal)
;	values should be 0 <= value <= 255
;
;	End of current sequence
;	-----------------------
;	fade_rate = 255 tells code that this is then end of the current
;	sequence data.
;
;	End of all sequence data
;	------------------------
;	fade_rate and hold_time = 255 tells the code that this is the end
; 	of the current sequence data AND the end of all sequences.
;
;	Fade Rate
;	---------
;	fade_rate = 0 --> no fade, new values update immediateley
;	fade_rate >0 and <255 fades from current to new values.
;	The colours fade from the current value to the new value
;	in steps of 1 (i.e. 0 to 100 requires 100 steps)
;	each step takes ~5mS x Fade Rate.
;
;	max fade time with increments of 5mS x fade_rate.
;	  1 x 5mS x 255 = 1.27 secs
;	  2 x 5mS x 255 = 2.50 secs
;	  3 x 5mS x 255 = 3.85 secs
;	  4 x 5mS x 255 = 5.10 secs
;	  5 x 5mS x 255 = 6.35 secs
;   6 x 5mS x 255 = 7.60 secs
;   ......
; 254 x 5mS x 255 = 3m23s
;
;	Hold Time
;	---------
;	How long to hold the current RGB colours before getting
; 	the next set of RGB values.
; 	hold_time = 0 --> no hold, jump to next step in sequence
;	hold_time >0 and <255 hold for 50ms x hold_time
;	1   x 50mS = 50mS
;	254 x 50mS = 12.7 secs
;
;	     |---------------------- Fade Rate
;      |    |----------------- Hold time
;      |    |    |------------ Red
;      |    |    |    |------- Green
;      |    |    |    |    |-- Blue
;      |    |    |    |    |


	dt   2 , 0,255,  0,  0
	dt   5 , 0,255, 40,  0
	dt   20, 0,255,200,  0
	dt   5 ,10,255,255,  0
	dt   5 ,15,  0,255,  0
	dt   5 ,10,  0,255,255
	dt   5 ,15,  0,  0,255
	dt   5 ,10,255,255,255

	dt   15,10,200,  0,  0
	dt   5 ,10,255,  0,  0
	dt   20,10,255,  0,200
	dt   5 ,10,255,  0,255

	dt   255		;seq 1


	;dt   0,0,255,  0,  0
	;dt   10,50,255,255,  0

	;dt   10,0,  0,255,  0
	;dt   10,0,  0,255,255

	;dt   10,0,  0,  0,255
	;dt   10,50,255,  0,255

	;dt   10,0,255,  0,  0

	;dt   5,0,255,255,255

	;dt   10,50,255,255,  0
	;dt   5,0,255,255,255

	;dt   10,50,255,  0,255
	;dt   5,0,255,255,255

	;dt   10, 0,  0,255,255

	;dt   255		;seq 1

	;dt   5, 5, 255,  0,  0
	;dt   5, 20,255,255,  0
	;dt   5, 5, 128,255,  0
	;dt   5, 5, 255,128,64
	;dt   5, 5,0,255,255
	;dt   5, 5, 255,255,128
	;dt   5, 5, 128,0,64
	;dt   5, 5, 255,0,128
	;dt   5, 5, 255,255,255
	;dt   5, 5,   0,0,255
	;dt   5, 5, 255,128,128
	;dt   5, 5,255,255,255
	;dt   5, 5,0,255,0
	;dt   255		;seq 1

	;dt   10, 10, 255,  0,  0
	;dt   10, 10, 128,  0,128
	;dt   10, 10, 128,255,128
	;dt   10, 15, 255,255,  0
	;dt   10, 10, 255,255,255
	;dt   10, 10,   0,255,255
	;dt   10, 10,   0,  0,255
	;dt   10, 10,   0,128,128
	;dt   10, 10, 255,128,128
	;dt   10, 10, 255,  0,255
	;dt   10, 10,   0,255,  0
	;dt   10, 15, 128,128,  0
	;dt   10, 10, 128,128,255

	;dt   255		;seq 1

	dt   8,  5, 160,   0,   0	; Spectum fade
	dt   8,  5, 160, 0,   160
	dt   8,  5,   0, 0,   160
	dt   8,  5,   0, 160, 160
	dt   8,  5,   0, 160,  0
	dt   8,  5, 160,   0,  160
	dt 255		 ; seq 2


	dt   6,   0,  255,  200,  24
	dt   6,   0,  200,  24, 255
	dt   6,   0,  24, 255, 200
	dt 255		; seq 3


	dt   23,   0,  255,  200,  24
	dt   23,   0,  24, 255, 200
	dt   23,   0,  200, 24, 255
	dt 255		;seq 4



	dt   30,   0, 255, 128, 0
	dt   30,   0, 128,255, 0
	dt 255		; end of sequence 5


	dt  30,   0, 255, 0, 128
	dt  30,   0, 128, 0, 255
	dt 255		; end of sequence 6



	dt   30,   0, 0,255,128
	dt   30,   2, 0,128,255
	dt 255		; end of sequence 7






	dt   0,   5, 255,   0,   0	;
	dt   1,   0,   0,   0,   0
	dt   0,   5,   0, 255,   0
	dt   1,   0,   0,   0,   0
	dt   0,   5,   0,   0, 255
	dt   1,   0,   0,   0,   0
	dt 255		; end of sequence 8


	dt   2,   5, 255,   0,   0	;
	dt   1,   0,   0,   0,   0
	dt   2,   5,   0, 255,   0
	dt   1,   0,   0,   0,   0
	dt   2,   5,   0,   0, 255
	dt   1,   0,   0,   0,   0
	dt 255		; end of sequence


	dt   2,   1, 255,   0,   0
	dt   2,   1,   0, 255,   0
	dt   2,   1,   0,   0, 255
	dt 255		; end of sequence


	dt   2,   1, 255,  64,   0
	dt   2,   1,  64,   0, 255
	dt   2,   1,   0, 255,  64
	dt 255		; end of sequence





	dt   0, 254, 240, 240, 240	; White Bright
	dt 255 		; end of sequence


	dt   0, 254, 128, 128, 128	; White Half
	dt 255 		; end of sequence


	dt   0, 254,  48,  48,  58	; White Low
	dt 255 		; end of sequence


	dt   6,  10, 255,   0,   0	; Spectum fade
	dt   6,  10, 255, 255,   0
	dt   6,  10,   0, 255,   0
	dt   6,  10,   0, 255, 255
	dt   6,  10,   0,   0, 255
	dt   6,  10, 255,   0, 255
	dt 255		 ; end of sequence


	dt  25, 5, 255,   0,   0	; Spectum fade slow
	dt  25, 5, 255, 255,   0
	dt  25, 5,   0, 255,   0
	dt  25, 5,   0, 255, 255
	dt  25, 5,   0,   0, 255
	dt  25, 5, 255,   0, 255
	dt 255		; end of sequence


	dt   4,  10, 254,  32,   0	; warm
	dt   4,  10, 254, 128,   0
	dt   4,  10, 254, 240,   0
	dt   4,  10, 128, 240,   0
	dt 255		; end of sequence


	dt   4,  10,   0,  16, 255	; cool
	dt   4,  10,   0, 128, 255
	dt   4,  10,   0, 240, 128
	dt   4,  10,   16, 16, 240
	dt   4,  10,  240, 16, 240
	dt   4,  10,   64,  0, 250
	dt 255		; end of sequence

	dt  10,   4, 240,   0, 240	; purple
	dt  10,   4,  32,   0, 240
	dt  10,   4, 128,   0, 128
	dt  10,   4, 240,   0,  32
	dt 255		 ; end of sequence

	dt   0,   1, 255,   0,   0  ; Cycle Red, Green, Blue. Cycle rate every 50mS
	dt   0,   1,   0, 255,   0
	dt   0,   1,   0,   0, 255
	dt 255		; end of sequence


	dt   0,   2, 255,   0,   0  ; Cycle Red, Green, Blue. Cycle rate every 100mS (1/10 second)
	dt   0,   2,   0, 255,   0
	dt   0,   2,   0,   0, 255
	dt 255		; end of sequence


	dt   0,   4, 255,   0,   0  ; Cycle Red, Green, Blue. Cycle rate every 200mS (1/5 second)
	dt   0,   4,   0, 255,   0
	dt   0,   4,   0,   0, 255
	dt 255		; end of sequence


	dt   0,   6, 255,   0,   0  ; Cycle Red, Green, Blue. Cycle rate every 300mS
	dt   0,   6,   0, 255,   0
	dt   0,   6,   0,   0, 255
	dt 255		; end of sequence


	dt   0,   8, 255,   0,   0  ; Cycle Red, Green, Blue. Cycle rate every 400mS
	dt   0,   8,   0, 255,   0
	dt   0,   8,   0,   0, 255
	dt 255		; end of sequence


	dt   0,  10, 255,   0,   0  ; Cycle Red, Green, Blue. Cycle rate every 500mS (1/2 second)
	dt   0,  10,   0, 255,   0
	dt   0,  10,   0,   0, 255
	dt 255		; end of sequence


	dt   0,  20, 255,   0,   0  ; Cycle Red, Green, Blue. Cycle rate every 1000mS (1 second)
	dt   0,  20,   0, 255,   0
	dt   0,  20,   0,   0, 255
	dt 255		; end of sequence





; flash to show firmware version
; G.R.B = 3.0.3
;
	dt   0,   5, 0, 15, 15		; red
	dt   0,   3,   0,   0,   0		; off
	dt   0,   5, 0, 15, 15		; red
	dt   0,   3,   0,   0,   0		; off
	dt   0,   5, 0, 15, 15		; red
	dt   0,   3,   0,   0,   0		; off
	dt   0,  20,   0,   0,   0		; off
	dt 255		; end of sequence


	dt 255		; end of all data


