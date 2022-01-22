;
; The code given to you here implements the histogram calculation that 
; we developed in class.  In programming lab, we will add code that
; prints a number in hexadecimal to the monitor.
;
; Your assignment for this program is to combine these two pieces of 
; code to print the histogram to the monitor.
;
; If you finish your program, 
;    ** commit a working version to your repository  **
;    ** (and make a note of the repository version)! **


	.ORIG	x3000		; starting address is x3000


;
; Count the occurrences of each letter (A to Z) in an ASCII string 
; terminated by a NUL character.  Lower case and upper case should 
; be counted together, and a count also kept of all non-alphabetic 
; characters (not counting the terminal NUL).
;
; The string starts at x4000.
;
; The resulting histogram (which will NOT be initialized in advance) 
; should be stored starting at x3F00, with the non-alphabetic count 
; at x3F00, and the count for each letter in x3F01 (A) through x3F1A (Z).
;
; table of register use in this part of the code
;    R0 holds a pointer to the histogram (x3F00)
;    R1 holds a pointer to the current position in the string
;       and as the loop count during histogram initialization
;    R2 holds the current character being counted
;       and is also used to point to the histogram entry
;    R3 holds the additive inverse of ASCII '@' (xFFC0)
;    R4 holds the difference between ASCII '@' and 'Z' (xFFE6)
;    R5 holds the difference between ASCII '@' and '`' (xFFE0)
;    R6 is used as a temporary register
;

	LD R0,HIST_ADDR      	; point R0 to the start of the histogram
	
	; fill the histogram with zeroes 
	AND R6,R6,#0		; put a zero into R6
	LD R1,NUM_BINS		; initialize loop count to 27
	ADD R2,R0,#0		; copy start of histogram into R2

	; loop to fill histogram starts here
HFLOOP	STR R6,R2,#0		; write a zero into histogram
	ADD R2,R2,#1		; point to next histogram entry
	ADD R1,R1,#-1		; decrement loop count
	BRp HFLOOP		; continue until loop count reaches zero

	; initialize R1, R3, R4, and R5 from memory
	LD R3,NEG_AT		; set R3 to additive inverse of ASCII '@'
	LD R4,AT_MIN_Z		; set R4 to difference between ASCII '@' and 'Z'
	LD R5,AT_MIN_BQ		; set R5 to difference between ASCII '@' and '`'
	LD R1,STR_START		; point R1 to start of string

	; the counting loop starts here
COUNTLOOP
	LDR R2,R1,#0		; read the next character from the string
	BRz PRINT_HIST		; found the end of the string

	ADD R2,R2,R3		; subtract '@' from the character
	BRp AT_LEAST_A		; branch if > '@', i.e., >= 'A'
NON_ALPHA
	LDR R6,R0,#0		; load the non-alpha count
	ADD R6,R6,#1		; add one to it
	STR R6,R0,#0		; store the new non-alpha count
	BRnzp GET_NEXT		; branch to end of conditional structure
AT_LEAST_A
	ADD R6,R2,R4		; compare with 'Z'
	BRp MORE_THAN_Z         ; branch if > 'Z'

; note that we no longer need the current character
; so we can reuse R2 for the pointer to the correct
; histogram entry for incrementing
ALPHA	ADD R2,R2,R0		; point to correct histogram entry
	LDR R6,R2,#0		; load the count
	ADD R6,R6,#1		; add one to it
	STR R6,R2,#0		; store the new count
	BRnzp GET_NEXT		; branch to end of conditional structure

; subtracting as below yields the original character minus '`'
MORE_THAN_Z
	ADD R2,R2,R5		; subtract '`' - '@' from the character
	BRnz NON_ALPHA		; if <= '`', i.e., < 'a', go increment non-alpha
	ADD R6,R2,R4		; compare with 'z'
	BRnz ALPHA		; if <= 'z', go increment alpha count
	BRnzp NON_ALPHA		; otherwise, go increment non-alpha

GET_NEXT
	ADD R1,R1,#1		; point to next character in string
	BRnzp COUNTLOOP		; go to start of counting loop



PRINT_HIST

; you will need to insert your code to print the histogram here

; do not forget to write a brief description of the approach/algorithm
; for your implementation, list registers used in this part of the code,
; and provide sufficient comments

; Registers
;	R0: Printing 
;	R1: Loop count
;	R2: Additive inverse of number of bins
;	R3: Loop counter for bin to hex printing
;	R4: Loop counter for transfer 4MSB of data to R0
;	R5: Histogram entry for character
;	R6: Temp Register

	; LD	R0, STR_START	; Printout the string  --THIS HEADER NOT USED FOR ACTUAL FORMAT--
	; PUTS

	; AND	R0, R0, #0	; Clear R0
	; ADD	R0, R0, x0A	; LD ascii code for newline
	; OUT			; Print 2 newline characters
	; OUT			--END OF UNUSED HEADER--

	AND	R1, R1, #0	; Set Loop count to 0
	LD	R2, NUM_BINS	; Set R2 to additive inverse of number of bins
	NOT	R2, R2
	ADD	R2, R2, #1

BINLOOP ; Print label for line
	LD	R0, ASCII_AT	; Load @ character into R0
	ADD	R0, R0, R1	; Add loop counter to make it into current character
	OUT			; Print it
	LD	R0, ASCII_SP	; Load space character into R0
	OUT			; Print it

	; Get count, convert to ascii hex and print
	LD	R6, HIST_ADDR	; Load starting address of histogram into R6
	ADD	R6, R6, R1	; Add loop counter to get addr of correct row in histogram
	LDR	R5, R6, #0	; Load number of occurences into R6

	AND	R3, R3, #0	; Clear R3
	ADD	R3, R3, #4	; Set R3 to 4 (for 4 digits)

BITLOOP	AND	R4, R4, #0	; Clear R4
	ADD	R4, R4, #4	; Set R4 to 4 (4 bits per hex digit)
	AND	R0, R0, #0	; Clear R0

DIGLOOP	; This loop transfers 4 MSB from data to R0 to be printed
	ADD	R0, R0, R0	; Leftshift R0
	ADD	R5, R5, #0	; Update CC bits with number of occurences data
	BRzp	NO_ADD		; if MSB of data 0, keep LSB of R0 0
	ADD	R0, R0, #1	; Set last bit of R0 to 1
NO_ADD	ADD	R5, R5, R5	; Leftshift data
	ADD	R4, R4, #-1	; Decrement bit loop
	BRp	DIGLOOP		; Loop 4 times

	ADD	R0, R0, #-10	; Test of number or letter digit
	BRzp	LETTER

	LD	R6, OFFSET_0	; Load ascii offset for number
	BR	PRINTCH

LETTER	LD	R6, OFFSET_A	; Load ascii offset for letter

PRINTCH	ADD	R0, R0, R6	; Add offset to turn R0 into ascii for correct hex digit
	OUT			; Print it

	ADD	R3, R3, #-1	; Decrement hex digit loop
	BRp	BITLOOP		; Loop 4 times
	
	; End of line code
	AND	R0, R0, #0	;Print newline
	ADD	R0, R0, x0A
	OUT
	ADD	R3, R3, #1	; Store next ascii character
	ADD	R1, R1, #1	; Increment loop counter
	ADD	R6, R1, R2	; Check if loop count is still < number of bins
	BRn	BINLOOP		; Next line if haven't printed number of bins lines


DONE	HALT			; done


; the data needed by the program
NUM_BINS	.FILL #27	; 27 loop iterations
NEG_AT		.FILL xFFC0	; the additive inverse of ASCII '@'
AT_MIN_Z	.FILL xFFE6	; the difference between ASCII '@' and 'Z'
AT_MIN_BQ	.FILL xFFE0	; the difference between ASCII '@' and '`'
HIST_ADDR	.FILL x3F00     ; histogram starting address
ASCII_AT	.FILL x0040	;+Ascii value for @
ASCII_SP	.FILL x0020	;+Ascii value for space
OFFSET_0	.FILL x003a	;+Ascii value for 0 + 10
OFFSET_A	.FILL x0041	;+Ascii value for A
STR_START	.FILL x4000	; string starting address


; for testing, you can use the lines below to include the string in this
; program...
; STR_START	.FILL STRING	; string starting address
; STRING		.STRINGZ "This is a test of the counting frequency code.  AbCd...WxYz."



	; the directive below tells the assembler that the program is done
	; (so do not write any code below it!)

	.END
