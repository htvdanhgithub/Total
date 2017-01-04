; ----------------------------------
; See pwmc_SeqMacro.inc for information on the format of the sequence data
;
; ----------------------------------
; seq 01
              control 0,4
              hold 8
              sdat 3,0,0,0,0,0,0,0
              hold 8
              sdat 2,3,0,0,0,0,0,0
              hold 8
              sdat 1,2,3,0,0,0,0,0
              hold 8
              sdat 1,1,2,3,0,0,0,0
              hold 8
              sdat 0,1,1,2,3,0,0,0
              hold 8
              sdat 0,0,1,1,2,3,0,0
              hold 8
              sdat 0,0,0,1,1,2,3,0
              hold 8
              sdat 0,0,0,0,1,1,2,3
              hold 8
              sdat 0,0,0,0,0,0,1,3
	hold 8
              sdat 0,0,0,0,0,0,0,3
              hold 8
              sdat 0,0,0,0,0,0,3,2
              hold 8
              sdat 0,0,0,0,0,3,2,1
              hold 8
              sdat 0,0,0,0,3,2,1,1
              hold 8
              sdat 0,0,0,3,2,1,1,0
              hold 8
              sdat 0,0,3,2,1,1,0,0
              hold 8
              sdat 0,3,2,1,1,0,0,0
              hold 8
              sdat 3,2,1,1,0,0,0,0
              hold 8
              sdat 3,1,0,0,0,0,0,0

              
              seqend

; ----------------------------------
; seq 02

              control 0,4
              hold 11
              sdat 3,0,0,0,0,0,0,0
              hold 11
              sdat 2,3,0,0,0,0,0,0
              hold 11
              sdat 1,2,3,0,0,0,0,0
              hold 11
              sdat 1,1,2,3,0,0,0,0
              hold 11
              sdat 0,1,1,2,3,0,0,0
              hold 11
              sdat 0,0,1,1,2,3,0,0
              hold 11
              sdat 0,0,0,1,1,2,3,0
              hold 11
              sdat 0,0,0,0,1,1,2,3
              hold 11
              sdat 0,0,0,0,0,0,1,3
	hold 11
              sdat 0,0,0,0,0,0,0,3
              hold 11
              sdat 0,0,0,0,0,0,3,2
              hold 11
              sdat 0,0,0,0,0,3,2,1
              hold 11
              sdat 0,0,0,0,3,2,1,1
              hold 11
              sdat 0,0,0,3,2,1,1,0
              hold 11
              sdat 0,0,3,2,1,1,0,0
              hold 11
              sdat 0,3,2,1,1,0,0,0
              hold 11
              sdat 3,2,1,1,0,0,0,0
              hold 11
              sdat 3,1,0,0,0,0,0,0

              
              seqend

; ----------------------------------
; seq 03

              control 0,4
              hold 45
              sdat 3,0,0,0,0,0,0,0
              hold 8
              sdat 2,3,0,0,0,0,0,0
              hold 8
              sdat 1,2,3,0,0,0,0,0
              hold 8
              sdat 1,1,2,3,0,0,0,0
              hold 8
              sdat 0,1,1,2,3,0,0,0
              hold 8
              sdat 0,0,1,1,2,3,0,0
              hold 8
              sdat 0,0,0,1,1,2,3,0
              hold 8
              sdat 0,0,0,0,1,1,2,3
              hold 8
              sdat 0,0,0,0,0,0,1,3
	hold 45
              sdat 0,0,0,0,0,0,0,3
              hold 8
              sdat 0,0,0,0,0,0,3,2
              hold 8
              sdat 0,0,0,0,0,3,2,1
              hold 8
              sdat 0,0,0,0,3,2,1,1
              hold 8
              sdat 0,0,0,3,2,1,1,0
              hold 8
              sdat 0,0,3,2,1,1,0,0
              hold 8
              sdat 0,3,2,1,1,0,0,0
              hold 8
              sdat 3,2,1,1,0,0,0,0
              hold 8
              sdat 3,1,0,0,0,0,0,0

              
              seqend

; ----------------------------------
; seq 04
              control 0,5

              hold 8
              sdat 1,0,0,0,0,0,0,1
              hold 8
	sdat 0,1,0,0,0,0,1,0
              hold 8
	sdat 0,0,1,0,0,1,0,0
              hold 8
	sdat 0,0,0,1,1,0,0,0
              hold 8
	sdat 1,0,0,1,1,0,0,1
              hold 8
	sdat 0,1,0,1,1,0,1,0
              hold 8
	sdat 0,0,1,1,1,1,0,0
              hold 8
	sdat 0,0,0,2,2,0,0,0
              hold 8
	sdat 0,0,0,2,2,0,0,0
              hold 8
	sdat 1,0,0,2,2,0,0,1
              hold 8
	sdat 0,1,0,2,2,0,1,0
              hold 8
	sdat 0,0,1,2,2,1,0,0
              hold 8
	sdat 0,0,0,3,3,0,0,0
              hold 8
	sdat 1,0,0,3,3,0,0,1
              hold 8
	sdat 0,1,0,3,3,0,1,0
              hold 8
	sdat 0,0,1,3,3,1,0,0
              hold 8
	sdat 0,0,0,3,3,0,0,0

              hold 8
	sdat 0,0,3,3,3,3,0,0
              hold 7
	sdat 0,3,3,3,3,3,3,0
              hold 6
	sdat 3,3,3,3,3,3,3,3
              hold 8
	sdat 3,3,3,2,2,3,3,3
              hold 10
	sdat 3,3,2,1,1,2,3,3
              hold 10
	sdat 3,2,1,0,0,1,2,3
              hold 10
	sdat 2,1,0,0,0,0,1,2
              hold 12
	sdat 1,0,0,0,0,0,0,1
	seqend

; ----------------------------------
; seq 05
              control 1,8

              hold 5
              sdat 1,3,1,0,0,0,0,0
              hold 5
              sdat 0,1,3,1,0,0,0,0
              hold 5
              sdat 0,0,1,3,1,0,0,0
              hold 5
              sdat 0,0,0,1,3,1,0,0
              hold 5
              sdat 0,0,0,0,1,3,1,0
              hold 5
              sdat 0,0,0,0,0,1,3,1
              hold 5
              sdat 1,0,0,0,0,0,1,3
              hold 5
              sdat 1,3,0,0,0,0,0,1
              seqend


; ----------------------------------
; seq 06
              control 1,8

              hold 3
              sdat 1,3,1,0,0,0,0,0
              hold 3
              sdat 0,1,3,1,0,0,0,0
              hold 3
              sdat 0,0,1,3,1,0,0,0
              hold 3
              sdat 0,0,0,1,3,1,0,0
              hold 3
              sdat 0,0,0,0,1,3,1,0
              hold 3
              sdat 0,0,0,0,0,1,3,1
              hold 3
              sdat 1,0,0,0,0,0,1,3
              hold 3
              sdat 1,3,0,0,0,0,0,1
              seqend


; ----------------------------------
; seq 07
              control 1,8

              hold 2
              sdat 3,0,0,0,0,0,0,0
              hold 2
              sdat 0,3,0,0,0,0,0,0
              hold 2
              sdat 0,0,3,0,0,0,0,0
              hold 2
              sdat 0,0,0,3,0,0,0,0
              hold 2
              sdat 0,0,0,0,3,0,0,0
              hold 2
              sdat 0,0,0,0,0,3,0,0
              hold 2
              sdat 0,0,0,0,0,0,3,0
              hold 2
              sdat 0,0,0,0,0,0,0,3

              hold 2
              sdat 3,0,0,0,0,0,0,0
              hold 2
              sdat 2,3,0,0,0,0,0,0
              hold 2
              sdat 1,2,3,0,0,0,0,0
              hold 2
              sdat 0,1,2,3,0,0,0,0
              hold 5
              sdat 0,0,1,2,3,0,0,0
              hold 7
              sdat 0,0,0,1,2,3,0,0
              hold 9
              sdat 0,0,0,0,1,2,3,0
              hold 11
              sdat 0,0,0,0,0,1,2,3
              hold 12
              sdat 0,0,0,0,0,0,1,2
              hold 14
              sdat 0,0,0,0,0,0,0,1

              seqend

; ----------------------------------
; seq 08
              control 1,3

              hold 1
              sdat 3,0,0,0,0,0,0,0
              hold 1
              sdat 0,3,0,0,0,0,0,0
              hold 1
              sdat 0,0,3,0,0,0,0,0
              hold 1
              sdat 0,0,0,3,0,0,0,0
              hold 1
              sdat 0,0,0,0,3,0,0,0
              hold 1
              sdat 0,0,0,0,0,3,0,0
              hold 1
              sdat 0,0,0,0,0,0,3,0
              hold 1
              sdat 0,0,0,0,0,0,0,3

              hold 3
              sdat 0,0,0,0,0,0,3,2
              hold 4
              sdat 0,0,0,0,0,3,2,1
              hold 5
              sdat 0,0,0,0,3,2,1,1
              hold 6
              sdat 0,0,0,3,2,1,1,1
              hold 7
              sdat 0,0,3,2,1,1,1,0
              hold 8
              sdat 0,3,2,1,1,1,0,0
              hold 9
              sdat 3,2,1,1,1,0,0,0
              hold 10
              sdat 2,1,1,0,0,0,0,0
              hold 11
              sdat 1,0,0,0,0,0,0,0
              hold 12
              sdat 0,0,0,0,0,0,0,0

              seqend

; ----------------------------------
; seq 09
              control 1,8

              hold 8
              sdat 3,0,0,0,0,0,1,2
              hold 8
              sdat 2,3,0,0,0,0,0,1
              hold 8
              sdat 1,2,3,0,0,0,0,0
              hold 8
              sdat 0,1,2,3,0,0,0,0
              hold 8
              sdat 0,0,1,2,3,0,0,0
              hold 8
              sdat 0,0,0,1,2,3,0,0
              hold 8
              sdat 0,0,0,0,1,2,3,0
              hold 8
              sdat 0,0,0,0,0,1,2,3

              seqend


; ----------------------------------
; seq 10
              control 0,10

              hold 8
              sdat 0,1,1,0,0,1,1,0
              hold 8
              sdat 1,2,2,1,1,2,2,1
              hold 8
              sdat 2,3,3,2,2,3,3,2
              hold 8
              sdat 3,2,2,3,3,2,2,3
              hold 8
              sdat 2,1,1,2,2,1,1,2
              hold 8
              sdat 1,0,0,1,1,0,0,1
              
              seqend
              

; ----------------------------------
; seq 11
              control 0,14

              hold 7
              sdat 1,0,0,0,0,0,0,1
              hold 7
              sdat 2,1,0,0,0,0,2,1
              hold 7
              sdat 3,2,1,0,0,1,2,3
              hold 7
              sdat 2,3,2,1,1,2,3,2
              hold 7
              sdat 1,2,3,2,2,3,2,1
              hold 7
              sdat 0,1,2,3,3,2,1,0
              hold 7
              sdat 0,0,1,2,2,1,0,0
              hold 7
              sdat 0,0,0,1,1,0,0,0
              hold 7
              sdat 0,0,0,0,0,0,0,0
              

              seqend
; ----------------------------------
; seq 12

              control 0,10

              hold 8
              sdat 2,2,0,0,2,2,0,0
              hold 8
              sdat 0,2,2,0,0,2,2,0
              hold 8
              sdat 0,0,2,2,0,0,2,2
              hold 8
              sdat 2,0,0,2,2,0,0,2

              seqend
; ----------------------------------
; seq 13

              control 1,4
              hold 100
              sdat 1,1,1,1,1,1,1,1
              hold 20
              sdat 2,1,1,1,1,1,1,1
              hold 20
              sdat 3,1,1,1,1,1,1,1
              hold 2
              sdat 1,3,1,1,1,1,1,1
              hold 2
              sdat 1,1,3,1,1,1,1,1
              hold 2
              sdat 1,1,1,3,1,1,1,1
              hold 2
              sdat 1,1,1,1,3,1,1,1
              hold 2
              sdat 1,1,1,1,1,3,1,1
              hold 2
              sdat 1,1,1,1,1,1,3,1
              hold 2
              sdat 1,1,1,1,1,1,1,3

              hold 2
              sdat 1,1,1,1,1,1,1,1
              hold 2
              sdat 3,1,1,1,1,1,1,1
              hold 2
              sdat 1,3,1,1,1,1,1,1
              hold 2
              sdat 1,1,3,1,1,1,1,1
              hold 2
              sdat 1,1,1,3,1,1,1,1
              hold 2
              sdat 1,1,1,1,3,1,1,1
              hold 2
              sdat 1,1,1,1,1,3,1,1
              hold 2
              sdat 1,1,1,1,1,1,3,1
              hold 2
              sdat 1,1,1,1,1,1,1,3

              seqend
; ----------------------------------
; seq 14
              control 0,4
              hold 7
              sdat 1,1,2,3,3,2,1,1
              hold 7
              sdat 1,2,3,3,2,1,1,1
              hold 7
              sdat 2,3,3,2,1,1,1,1
              hold 7
              sdat 1,3,2,1,1,1,1,1
              hold 7
              sdat 2,3,3,2,1,1,1,1
              hold 7
              sdat 1,2,3,3,2,1,1,1
              hold 7
              sdat 1,1,1,2,3,3,2,1
              hold 7
              sdat 1,1,1,1,2,3,3,2
              hold 7
              sdat 1,1,1,1,1,2,3,3
              hold 7
              sdat 1,1,1,1,2,3,3,2
              hold 7
              sdat 1,1,1,2,3,3,2,1

              seqend
; ----------------------------------
; seq 15

              control 0,4
              hold 7
              sdat 3,1,1,1,1,1,1,1
              hold 7
              sdat 2,3,1,1,1,1,1,1
              hold 7
              sdat 1,2,3,1,1,1,1,1
              hold 7
              sdat 1,1,2,3,1,1,1,1
              hold 7
              sdat 1,1,1,2,3,1,1,1
              hold 7
              sdat 1,1,1,1,2,3,1,1
              hold 7
              sdat 1,1,1,1,1,2,3,1
              hold 7
              sdat 1,1,1,1,1,1,2,3
              hold 7
              sdat 1,1,1,1,1,1,1,3
              hold 7
              sdat 1,1,1,1,1,1,3,2
              hold 7
              sdat 1,1,1,1,1,3,2,1
              hold 7
              sdat 1,1,1,1,3,2,1,1
              hold 7
              sdat 1,1,1,3,2,1,1,1
              hold 7
              sdat 1,1,3,2,1,1,1,1
              hold 7
              sdat 1,3,2,1,1,1,1,1
              hold 7
              sdat 3,2,1,1,1,1,1,1
              
              seqend

; ----------------------------------
; seq 16
              control 0,6
              hold 7
              sdat 1,0,0,0,0,0,0,1
              hold 7
              sdat 0,1,0,0,0,0,1,0
              hold 7
              sdat 0,0,1,0,0,1,0,0
              hold 7
              sdat 0,0,0,1,1,0,0,0
              
              hold 7
              sdat 1,0,0,1,1,0,0,1
              hold 7
              sdat 0,1,0,1,1,0,1,0
              hold 7
              sdat 0,0,1,1,1,1,0,0
              hold 7
              sdat 0,0,0,2,2,0,0,0

              hold 7
              sdat 1,0,0,2,2,0,0,1
              hold 7
              sdat 0,1,0,2,2,0,1,0
              hold 7
              sdat 0,0,1,2,2,1,0,0
              hold 9
              sdat 0,0,0,3,3,0,0,0
              hold 9
              sdat 0,0,0,2,2,0,0,0
              hold 9
              sdat 0,0,0,1,1,0,0,0
              hold 9
              sdat 0,0,0,2,2,0,0,0
              hold 9
              sdat 0,0,0,3,3,0,0,0
              hold 3 
              sdat 0,0,3,2,2,3,0,0
              hold 4
              sdat 0,3,2,1,1,2,3,0
              hold 5
              sdat 3,2,1,0,0,1,2,3
              hold 6
              sdat 2,1,0,0,0,0,1,2
              hold 7
              sdat 1,0,0,0,0,0,0,1
              hold 7
              sdat 0,0,0,0,0,0,0,0

              seqend

; ----------------------------------
; seq 17
              control 1,31
              hold 7
              sdat 3,0,0,0,3,0,0,0
              hold 7
              sdat 0,3,0,0,0,3,0,0
              hold 7
              sdat 0,0,3,0,0,0,3,0
              hold 7
              sdat 0,0,0,3,0,0,0,3
              
              seqend

; ----------------------------------
; seq 18

              control 1,31
              hold 7
              sdat 3,2,1,0,3,2,1,0
              hold 7
              sdat 0,3,2,1,0,3,2,1
              hold 7
              sdat 1,0,3,2,1,0,3,2
              hold 7
              sdat 2,1,0,3,2,1,0,3
              
              seqend

; ----------------------------------
; seq 19
              control 0,9
              hold 9
              sdat 3,2,1,0,0,1,2,3
              hold 9
              sdat 3,3,2,1,1,2,3,3
              hold 9
              sdat 3,3,3,2,2,3,3,3
              hold 9
              sdat 3,3,3,3,3,3,3,3
              hold 9
              sdat 2,3,3,3,3,3,3,2
              hold 9
              sdat 1,2,3,3,3,3,2,1
              hold 9
              sdat 0,1,2,3,3,2,1,0
              hold 9
              sdat 0,0,1,2,2,1,0,0
              hold 9
              sdat 0,0,0,1,1,0,0,0
              hold 9
              sdat 0,0,0,0,0,0,0,0

              seqend

; ----------------------------------
; seq 20

              control 1,12
              hold 6
              sdat 3,2,1,0,0,0,1,2
              hold 6
              sdat 2,3,2,1,0,0,0,1
              hold 6
              sdat 1,2,3,2,1,0,0,0
              hold 6
              sdat 0,1,2,3,2,1,0,0
              hold 6
              sdat 0,0,1,2,3,2,1,0
              hold 6
              sdat 0,0,0,1,2,3,2,1
              hold 6
              sdat 1,0,0,0,1,2,3,2
              hold 6
              sdat 2,1,0,0,0,1,2,3

              seqend

; ----------------------------------
; seq 21

              control 1,4
              hold 6
              sdat 1,0,0,0,0,0,0,0
              hold 6
              sdat 0,1,0,0,0,0,0,0
              hold 6
              sdat 0,0,1,0,0,0,0,0
              hold 6
              sdat 0,0,0,1,0,0,0,0
              hold 6
              sdat 0,0,0,0,1,0,0,0
              hold 6
              sdat 0,0,0,0,0,1,0,0
              hold 6
              sdat 0,0,0,0,0,0,1,0
              hold 6
              sdat 0,0,0,0,0,0,0,2

              hold 6
              sdat 1,0,0,0,0,0,0,2
              hold 6
              sdat 0,1,0,0,0,0,0,2
              hold 6
              sdat 0,0,1,0,0,0,0,2
              hold 6
              sdat 0,0,0,1,0,0,0,2
              hold 6
              sdat 0,0,0,0,1,0,0,2
              hold 6
              sdat 0,0,0,0,0,1,0,2
              hold 6
              sdat 0,0,0,0,0,0,2,2
              

              hold 6
              sdat 1,0,0,0,0,0,2,2
              hold 6
              sdat 0,1,0,0,0,0,2,2
              hold 6
              sdat 0,0,1,0,0,0,2,2
              hold 6
              sdat 0,0,0,1,0,0,2,2
              hold 6
              sdat 0,0,0,0,1,0,2,2
              hold 6
              sdat 0,0,0,0,0,2,2,2
              
              hold 6
              sdat 1,0,0,0,0,2,2,2
              hold 6
              sdat 0,1,0,0,0,2,2,2
              hold 6
              sdat 0,0,1,0,0,2,2,2
              hold 6
              sdat 0,0,0,1,0,2,2,2
              hold 6
              sdat 0,0,0,0,2,2,2,2
              
              hold 6
              sdat 1,0,0,0,2,2,2,2
              hold 6
              sdat 0,1,0,0,2,2,2,2
              hold 6
              sdat 0,0,1,0,2,2,2,2
              hold 6
              sdat 0,0,0,2,2,2,2,2
              
              hold 6
              sdat 1,0,0,2,2,2,2,2
              hold 6
              sdat 0,1,0,2,2,2,2,2
              hold 6
              sdat 0,0,2,2,2,2,2,2
              
              hold 6
              sdat 1,0,2,2,2,2,2,2
              hold 6
              sdat 0,2,2,2,2,2,2,2
              
              hold 6
              sdat 2,2,2,2,2,2,2,2
              
              hold 6
              sdat 3,3,3,3,3,3,3,3
              hold 1
              sdat 0,0,0,0,0,0,0,0
              
              seqend

; ----------------------------------
; seq 22

	control 0,10
              hold 9
              sdat 3,3,0,0,0,0,3,3
	hold 6
              sdat 0,0,0,0,0,0,0,0
	hold 9
              sdat 3,3,0,0,0,0,3,3
	hold 6
              sdat 0,0,0,0,0,0,0,0

	hold 9
              sdat 0,0,3,3,3,3,0,0
	hold 6
              sdat 0,0,0,0,0,0,0,0
	hold 9
              sdat 0,0,3,3,3,3,0,0
	hold 6
              sdat 0,0,0,0,0,0,0,0

	seqend

; ----------------------------------

; seq 23

	control 0,10
              hold 9
              sdat 3,3,1,1,1,1,3,3
	hold 6
              sdat 0,0,1,1,1,1,0,0
	hold 9
              sdat 3,3,1,1,1,1,3,3
	hold 6
              sdat 0,0,1,1,1,1,0,0

	hold 9
              sdat 1,1,3,3,3,3,1,1
	hold 6
              sdat 1,1,0,0,0,0,1,1
	hold 9
              sdat 1,1,3,3,3,3,1,1
	hold 6
              sdat 1,1,0,0,0,0,1,1

	seqend

; ----------------------------------