.ORIG x3000
; Write code to read in characters and echo them
; till a newline character is entered.

; Registers
; R0 - IO
; R1 - String pointer
; R6 - Temp Register
; R7 - Temp Register 2

        LEA     R1, ST_START    	; Pointer to start of string

INPUT	IN

        LD	R6, NEW_LINE	; Check if NEW_LINE, get additive inverse
	NOT	R6, R6
	ADD	R6, R6, #1
	ADD	R6, R6, R0	; Add R0 (current character) to R6 (additive inverse of NEW_LINE)
	BRz	ENDLINE

	LD	R6, CHAR_RETURN	; Check if CHAR_RETURN, get additive inverse
	NOT	R6, R6
	ADD	R6, R6, #1
	ADD	R6, R6, R0	; Add R0 (current character) to R6 (additive inverse of NEW_LINE)
	BRz	ENDLINE

	STR     R0, R1, #0	; Append char to string 
	ADD	R1, R1, #1	; Increment next char pointer

        JSR     IS_BALANCED     ; Does the stack thing

        BRnzp    INPUT

;ADD code ot save R2 and R3
ENDLINE	AND	R5, R5, #0
	LD	R2, STACK_TOP
	LD	R3, STACK_START
	NOT	R2, R2
	ADD	R3, R3, R2	
	ADD	R3, R3, #1
	BRz	BALANCE

	ADD	R5, R5, #-1
	BRnzp	DONE

BALANCE	ADD	R5, R5, #1


DONE    AND	R0, R0, #0	; Clear R0 (set R0 to null)
	STR	R0, R1, #0	; Set next char in string to null (null-terminate it)

	LEA     R0, ST_START	; Print out string
        PUTS

        HALT			
 
SPACE		.FILL x0020
NEW_LINE	.FILL x000A
CHAR_RETURN	.FILL x000D
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;if ( push onto stack if ) pop from stack and check if popped value is (
;input - R0 holds the input
;output - R5 set to -1 if unbalanced. else 1.
IS_BALANCED
	LD	R6, NEG_OPEN	; Check if CHAR_RETURN, get additive inverse
	ADD	R6, R6, R0	; Add R0 (current character) to R6 (additive inverse of NEW_LINE)
	BRz	OPEN_P

	ST	R7, BAL_R7
	JSR	POP
	LD	R7, BAL_R7

	AND	R5, R5, #-1	; AND with xFFFF to reload R5 CC bits

	BRnz	MATCH

	AND	R5, R5, #0	; If they don't match, set R5 to -1 and end
	ADD	R5, R5, #-1
	BRnzp	DONE

	
OPEN_P	ST	R7, BAL_R7
	JSR	PUSH
	LD	R7, BAL_R7

MATCH	RET

BAL_R7	.BLKW	#1	


NEG_OPEN .FILL xFFD8
;IN:R0, OUT:R5 (0-success, 1-fail/overflow)
;R3: STACK_END R4: STACK_TOP
;
PUSH
        ST R3, PUSH_SaveR3      ;save R3
        ST R4, PUSH_SaveR4      ;save R4
        AND R5, R5, #0          ;
        LD R3, STACK_END        ;
        LD R4, STACk_TOP        ;
        ADD R3, R3, #-1         ;
        NOT R3, R3              ;
        ADD R3, R3, #1          ;
        ADD R3, R3, R4          ;
        BRz OVERFLOW            ;stack is full
        STR R0, R4, #0          ;no overflow, store value in the stack
        ADD R4, R4, #-1         ;move top of the stack
        ST R4, STACK_TOP        ;store top of stack pointer
        BRnzp DONE_PUSH         ;
OVERFLOW
        ADD R5, R5, #1          ;
DONE_PUSH
        LD R3, PUSH_SaveR3      ;
        LD R4, PUSH_SaveR4      ;
        RET


PUSH_SaveR3     .BLKW #1        ;
PUSH_SaveR4     .BLKW #1        ;


;OUT: R0, OUT R5 (0-success, 1-fail/underflow)
;R3 STACK_START R4 STACK_TOP
;
POP
        ST R3, POP_SaveR3       ;save R3
        ST R4, POP_SaveR4       ;save R3
        AND R5, R5, #0          ;clear R5
        LD R3, STACK_START      ;
        LD R4, STACK_TOP        ;
        NOT R3, R3              ;
        ADD R3, R3, #1          ;
        ADD R3, R3, R4          ;
        BRz UNDERFLOW           ;
        ADD R4, R4, #1          ;
        LDR R0, R4, #0          ;
        ST R4, STACK_TOP        ;
        BRnzp DONE_POP          ;
UNDERFLOW
        ADD R5, R5, #1          ;
DONE_POP
        LD R3, POP_SaveR3       ;
        LD R4, POP_SaveR4       ;
        RET


POP_SaveR3      .BLKW #1        ;
POP_SaveR4      .BLKW #1        ;
STACK_END       .FILL x3FF0     ;
STACK_START     .FILL x4000     ;
STACK_TOP       .FILL x4000     ;

ST_START        .BLKW #1        ; Start of String storage

.END

