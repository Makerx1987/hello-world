DATA    SEGMENT
MESS    DB 'Push any key to stop!',0dH,0aH,'$'
TABLE   DW  524,588,660,698,784,880,988,1048,1176,1320,0
TABLEL  DB  31H,31H,32H,31H,34H,33H,3BH
         DB  31H,31H,32H,31H,35H,34H,3BH
         DB  31H,31H,38H,36H,34H,33H,32H,3BH
         DB  36H,36H,36H,34H,35H,34H,3BH,0AAH
DATA    ENDS
STACK   SEGMENT  PARA  STACK  'STACK'
STA      DB  256 DUP(?)
STACK   ENDS
CODE    SEGMENT
          ASSUME  CS: CODE, DS: DATA, SS: STACK, ES: DATA
START    PROC  FAR
          PUSH  DS
          XOR  AX,  AX
          PUSH  AX
          MOV  AX,  DATA
          MOV  DS,  AX
          MOV  ES,  AX
          MOV  AH,  09H
          LEA  DX,  MESS
          INT  21H
KK:       LEA  SI,  TABLEL

SING:     MOV  AH,  06H
          MOV  DL,  0FFH
          INT  21H
          JNE  FINISH
          MOV  AL,  [SI]
          CMP  AL,  3BH
          JNE  DDD
          CALL  DELAY
          JMP  QQ
DDD:     CMP  AL,  0AAH
          JE  KK
          SUB  AL,  31H
          SHL  AL,  01H
          MOV  BL,  AL
          MOV  AX,  0000H
          MOV  DX,  12H
          MOV  BH,  00H
        DIV  WORD  PTR  [TABLE+BX]
        MOV  BX,  AX
        MOV  AL,  10110110B
        OUT  43H,  AL
        MOV  AX,  BX
        OUT  42H,  AL
        MOV  AL,  AH
        OUT  42H,  AL
        IN  AL,  61H
        OR  AL,  03H
        OUT  61H,  AL
        CALL  DELAY
        IN  AL,  61H
        AND  AL,  0FCH
        OUT  61H,  AL
QQ:     INC  SI
        JMP  SING
        FINISH:   RET
        START   ENDP          

DELAY  PROC  NEAR      ;    延时子程序
        PUSH  CX
        PUSH  AX
        MOV  AX,  50H   ;    大循环次数
        X1:    MOV  CX,  0FFFH  ; 小循环次数
        X2:    DEC  CX
        JNZ  X2
        DEC  AX
        JNZ  X1
        POP  AX
        POP  CX
        RET
        DELAY  ENDP 
CODE   ENDS
END  START
