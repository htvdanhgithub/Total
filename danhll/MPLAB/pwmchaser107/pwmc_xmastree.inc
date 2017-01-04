; ----------------------------------
; See pwmc_SeqMacro.inc for information on the format of the sequence data
;
; ----------------------------------
              control 0,5

	hold 10
	sdat 0,1,0,0,0,0,0,0

	hold 10
	sdat 1,0,1,0,0,0,0,0
	
	hold 10
	sdat 0,0,0,1,1,0,0,0

	hold 10
	sdat 0,0,0,0,0,1,1,0

	hold 10
	sdat 0,0,0,0,0,0,0,1

	hold 10
	sdat 0,1,0,0,0,0,0,1

	hold 10
	sdat 1,0,1,0,0,0,0,1
	
	hold 10
	sdat 0,0,0,1,1,0,0,1

	hold 10
	sdat 0,0,0,0,0,1,1,1

	hold 10
	sdat 0,0,0,0,0,0,0,2

	hold 10
	sdat 0,1,0,0,0,0,0,2

	hold 10
	sdat 1,0,1,0,0,0,0,2
	
	hold 10
	sdat 0,0,0,1,1,0,0,2

	hold 10
	sdat 0,0,0,0,0,1,1,2

	hold 10
	sdat 0,0,0,0,0,0,0,3

	hold 8
	sdat 0,0,0,0,0,0,0,0

	hold 2
	sdat 0,0,0,0,0,0,0,3

	hold 8
	sdat 0,0,0,0,0,0,0,0

	hold 2
	sdat 0,0,0,0,0,0,0,3

	hold 8
	sdat 0,0,0,0,0,0,0,0

	hold 2
	sdat 0,0,0,0,0,0,0,3

	hold 8
	sdat 0,0,0,0,0,0,0,0

	seqend


; ----------------------------------
              control 0,5

	hold 10
	sdat 1,1,1,0,0,0,0,0

	hold 10
	sdat 1,1,1,1,1,0,0,0

	hold 10 
	sdat 1,1,1,1,1,1,1,0
	
	hold 10
	sdat 1,1,1,1,1,1,1,1

	hold 8
	sdat 2,2,2,1,1,1,1,1

	hold 8 
	sdat 2,2,2,2,2,1,1,1

	hold 8
	sdat 2,2,2,2,2,2,2,1
	
	hold 8
	sdat 2,2,2,2,2,2,2,2

	hold 6
	sdat 3,3,3,2,2,2,2,2

	hold 6
	sdat 3,3,3,3,3,2,2,2

	hold 6
	sdat 3,3,3,3,3,3,3,2

	hold 6
	sdat 3,3,3,3,3,3,3,3

	hold 6
	sdat 2,2,2,3,3,3,3,3

	hold 6
	sdat 1,1,1,2,2,3,3,3

	hold 6
	sdat 0,0,0,1,1,2,2,3
	
	hold 6
	sdat 0,0,0,0,0,1,1,2

	hold 6
	sdat 0,0,0,0,0,0,0,1


	hold 6
	sdat 0,0,0,0,0,0,0,0

	seqend


; ----------------------------------
              control 0,5

	hold 10
	sdat 1,1,1,1,1,1,1,3
	
	hold 10
	sdat 1,1,1,1,1,3,1,1

	hold 10
	sdat 1,1,1,1,1,1,3,1
	

	hold 8
	sdat 1,1,1,1,1,1,1,3
	
	hold 8
	sdat 1,1,1,1,1,3,1,1

	hold 8
	sdat 1,1,1,1,1,1,3,1
	
	hold 6
	sdat 1,1,1,1,1,1,1,3
	
	hold 6
	sdat 1,1,1,1,1,3,1,1

	hold 6
	sdat 1,1,1,1,1,1,3,1


	hold 4
	sdat 1,1,1,1,1,1,1,3
	
	hold 4
	sdat 1,1,1,1,1,3,1,1

	hold 4
	sdat 1,1,1,1,1,1,3,1

	hold 6
	sdat 1,1,1,1,1,1,1,3
	
	hold 6
	sdat 1,1,1,1,1,3,1,1

	hold 6
	sdat 1,1,1,1,1,1,3,1

	hold 8
	sdat 1,1,1,1,1,1,1,3
	
	hold 8
	sdat 1,1,1,1,1,3,1,1

	hold 8
	sdat 1,1,1,1,1,1,3,1
	

	seqend

; ----------------------------------
              control 0,5

	hold 30
	sdat 2,2,2,1,1,1,1,1
	
	hold 30
	sdat 1,1,1,2,2,1,1,1

	hold 30
	sdat 1,1,1,1,1,2,2,1
	
	hold 30
	sdat 1,1,1,1,1,1,1,2

	seqend

; ----------------------------------
              control 0,5

	hold 30
	sdat 1,1,1,0,0,0,0,0
	
	hold 30
	sdat 0,0,0,1,1,0,0,0

	hold 30
	sdat 0,0,0,0,0,1,1,0
	
	hold 30
	sdat 0,0,0,0,0,0,0,1


	seqend


; ----------------------------------
	control 1,5
	
	hold 2
	sdat 1,1,1,3,1,1,1,1
	hold 20
	sdat 1,1,1,1,1,1,1,1

	hold 2
	sdat 3,1,1,1,1,1,1,1
	hold 50
	sdat 1,1,1,1,1,1,1,1

	hold 2
	sdat 1,1,1,3,1,1,1,1
	hold 35
	sdat 1,1,1,1,1,1,1,1

	hold 2
	sdat 1,3,1,1,1,1,1,1
	hold 55
	sdat 1,1,1,1,1,1,1,1

	hold 2
	sdat 1,1,1,1,1,1,1,3
	hold 65
	sdat 1,1,1,1,1,1,1,1

	hold 2
	sdat 1,1,3,1,1,1,1,1
	hold 45
	sdat 1,1,1,1,1,1,1,1

	hold 2
	sdat 1,1,1,1,1,3,1,1
	hold 40
	sdat 1,1,1,1,1,1,1,1

	hold 2
	sdat 1,1,1,1,3,1,1,1
	hold 50
	sdat 1,1,1,1,1,1,1,1

	hold 2
	sdat 3,1,1,1,1,1,1,1
	hold 45
	sdat 1,1,1,1,1,1,1,1

	hold 2
	sdat 1,1,1,3,1,1,1,1
	hold 35
	sdat 1,1,1,1,1,1,1,1

	hold 2
	sdat 1,1,3,1,1,1,1,1
	hold 55
	sdat 1,1,1,1,1,1,1,1

	hold 2
	sdat 1,1,1,1,1,1,1,3
	hold 60
	sdat 1,1,1,1,1,1,1,1

	hold 2
	sdat 1,1,1,1,1,3,1,1
	hold 45
	sdat 1,1,1,1,1,1,1,1

	hold 2
	sdat 1,3,1,1,1,1,1,1
	hold 55
	sdat 1,1,1,1,1,1,1,1

	hold 2
	sdat 1,1,1,1,1,1,3,1
	hold 40
	sdat 1,1,1,1,1,1,1,1

	hold 2
	sdat 1,3,1,1,1,1,1,1
	hold 65
	sdat 1,1,1,1,1,1,1,1

	hold 2
	sdat 1,1,3,1,1,1,1,1
	hold 45
	sdat 1,1,1,1,1,1,1,1

	seqend





; ----------------------------------
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



; ----------------------------------

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

