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
;            |    |----------------- Hold time
;            |    |    |------------ Red
;            |    |    |    |------- Green
;            |    |    |    |    |-- Blue
;            |    |    |    |    |


	dt   50, 20, 255, 0  ,   0  ; ?? 10
	dt   25, 20, 128, 40 ,   0  ; Cam ??m 5
	dt   25, 20, 255, 128,   0  ; Cam
	dt   25, 20, 255, 255,   0  ; Vàng
	dt   25, 20, 128, 255,   0  ; Xanh lá chu?i
	dt   25, 20,   0, 255,   0  ; Xanh lá chu?i ??m

	dt   25, 20,   0, 255, 255  ; L?c
	dt   15, 10, 255, 255, 255  ; Tr?ng
	dt   25, 40,   0,   0, 255  ; Xanh d??ng
	dt   25, 20, 128,   0, 128  ; Tím
	dt   25, 20, 255,   0, 255  ; H?ng
	dt   25, 20, 255,   0, 128  ; ?? bordeaux

	dt   255		;seq 1





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


