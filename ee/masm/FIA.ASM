   DATA     SEGMENT
   BUFFER   DB   10,22,33,-80,127,-76,0,90,-45,60,-1
   MINVAL   DB   ?
   MAXVAL  DB   ?
   DATA     ENDS
   STACK    SEGMENT  PARA  STACK  'STACK'
   STA       DB  100 DUP(?)
   STACK    ENDS
   CODE     SEGMENT
             ASSUME  CS:CODE, DS:DATA, ES:DATA, SS:STACK
   START     PROC   FAR
             PUSH  DS
             MOV  AX,  0
             PUSH  AX
             MOV  AX,  DATA
             MOV  DS,  AX
             MOV  ES,  AX
             LEA  BX,  BUFFER
             MOV  CH,  0
             MOV  CL,  [BX]
             INC  BX
             MOV  AL,  [BX]
             MOV  MINVAL,  AL
             MOV  MAXVAL,  AL
             INC  BX
             DEC  CX
   AGAIN:    MOV  AL,  [BX]
             CMP  AL,  MINVAL
             JE  NEXT
             JG  A1
             MOV  MINVAL,  AL
             JMP  NEXT
   A1:       CMP  AL,  MAXVAL
             JL  NEXT
             MOV  MAXVAL,  AL
   NEXT:    INC  BX
            DEC  CX
            JNE  AGAIN
            RETF
   START   ENDP
   CODE    ENDS  
END  START
