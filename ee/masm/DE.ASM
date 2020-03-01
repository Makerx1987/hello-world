   DATA     SEGMENT
   BUFFER   DB   10,22,33,-80,127,-76,0,90,-45,60,-1
   KEY   DB   -76
   FLAG  DB   0
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
             DEC  CX
   AGAIN:    MOV  AL,  [BX]
             CMP  AL,  KEY
             JNE  NEXT
             JE  DEL
   DEL:      MOV  AL,[BX+1]
             MOV  [BX],AL          
             INC BX
             DEC CX
             JE  FINISH1
             JNE  DEL
   NEXT:    INC  BX
            DEC  CX
            JNE  AGAIN
            MOV  FLAG,0FFH
            JMP FINISH2
  FINISH1:  MOV AL,0
            MOV [BX],AL
  FINISH2:  RETF
   START   ENDP
   CODE    ENDS  
END  START
