# L12_Stack_Detective_Computability
## 上节回顾
### 程序示例
在上一节中,我们学会了怎么样调用递归函数,下面就是一个简单的例子:
这是上一节的fact函数:
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

### 基址针(Base Pointer)

0111|01 11|111 0|0001| 0000 0000 0001 0100
