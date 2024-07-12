# L12_Stack_Detective_Computability
```asm
fact:   PUSH(LP)
        PUSH(BP)
        MOVE(SP,BP)
        PUSH(r1)
        LD(BP,-12,r1)
        CMPLEC(r1,0,r0)
        BT(r0,else)

        SUBC(r1,1,r1)
        PUSH(r1)
        BR(fact,LP)
        DEALLOCATE(1)
        LD(BP,-12,r1)
        MUL(r1,r0,r0)
        BR(rtn)

else:   CMOVE(1,r0)

rtn:    POP(r1)
        MOVE(BP,SP)
        POP(BP)
        POP(LP)
        JMP(LP)
```