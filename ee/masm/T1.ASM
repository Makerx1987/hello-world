DSEG		SEGMENT
STRING		DB	'Welcome to DONG HUA University!',0dH,0aH,'$'
DSEG		ENDS
STACK      SEGMENT	PARA  STACK 'STACK'
            DB		256	DUP (?)
STACK		ENDS
CSEG		SEGMENT
MAIN		PROC	FAR
            ASSUME  CS:  CSEG, DS: DSEG,  SS: STACK
START:		PUSH	DS
            MOV	AX,		0
            PUSH	AX
            MOV	AH,		9
            MOV	DX,		SEG	 STRING
            MOV	DS,     DX
            MOV	DX,		OFFSET  STRING
            INT		21H
            RET
MAIN		ENDP
CSEG		ENDS
        END	START
