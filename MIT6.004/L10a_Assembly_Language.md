# L10a_Assembly_Language(汇编语言)
## 使用范例
![L10a_UASM_Example.png](./Image/L10a_UASM_Example.png)

这是一张简单的汇编语言,下面我将介绍一下它的几个元素:
- <font color=Chartreuse>" // "</font> :这是注释
- <font color=CornflowerBlue>"ADDC"</font> :这是ALU指令(或者说是宏)
- <font color=Crimson>"N"</font> :符号,用来表示常数
- <font color=Gold>"loop"</font> :标签,用来表示地址

**下面介绍如何使用这些元素**
![L10a_Assembled_To_Binary.png](./Image/L10a_Assembled_To_Binary.png)

首先明确一个概念:
寄存器r0,r1,r2...r31 使用的是<font color=Crimson>红色</font>标签,也就是说,它门指代的都是常量r0=0;r1=1...

让我们一行一行来解读
- <font color=Crimson>N</font> = 12:
    把N添加到符号表中,并赋值12

- <font color=CornflowerBlue>ADDC</font>(<font color=Crimson>r31</font>,<font color=Crimson>N</font>,<font color=Crimson>r1</font>)
    查表得到N = 12,将r31指向的内存中的数据与常量N相加,并赋值到r1指向的地址
    $r1 = r31 + N[0x00]$
    机器码为:
    <font color=CornflowerBlue>110000</font> <font color=Crimson>00001</font> <font color=Crimson>11111</font> 00000000 00001100
    
- <font color=CornflowerBlue>ADDC</font>(<font color=Crimson>r31</font>,1,<font color=Crimson>r0</font>)
    将r31指向的内存中的数据与常量1相加,并赋值到r0指向的地址
    $r0 = r31 + 1[0x04]$
    机器码为:
    <font color=CornflowerBlue>110000</font> <font color=Crimson>00000</font> <font color=Crimson>11111</font> 00000000 00000001

- <font color=Gold>loop</font>: <font color=CornflowerBlue>MUL</font>(<font color=Crimson>r0</font>,<font color=Crimson>r1</font>,<font color=Crimson>r0</font>)
    1. 将标签loop放到符号表中,值为其所在的地址(0x08)
    2. 执行乘法运算$r0 = r0 * r1$
    
    机器码为:
    <font color=CornflowerBlue>100100</font> <font color=Crimson>00000</font> <font color=Crimson>00000</font> <font color=Crimson>00001</font> 00000000000

## 偏移与跳转
![L10a_Labels_and_Ofset.png](./Image/L10a_Labels_and_Ofset.png)

重点:Offset == -1

offset计算
$$
\begin{align}
offset =& (label - <addr of BNE/BEQ>)/4 -1\\
=&(0x08 - 0x10)/4 - 1\\
=&-3
\end{align}
$$
