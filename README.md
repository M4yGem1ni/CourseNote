# Lecture2 The meaning of Abstraction

## 概要
在本节中,我们将会探讨硬件、操作系统、程序之间的关系,也会介绍连接他们三者的一种力量---**抽象**.
我们将从CMOS开始,一步步构建出一套完整的系统,形成对计算机科学的一个初步认知,对计算机祛魅.

使用Mermaid画出思维导图
## 涵盖内容
- CMOS(简单讲)
    - 什么是MOSFET
    - INV(非门):CMOS基本单元

- 逻辑门(简单讲,留个印象)
    - 逻辑门是什么
        - 什么是真值表
    - CMOS与逻辑门
        - NAND(与非门)
        - NOR(或非门)
        - AND(与门)
        - OR(或门)
    - 逻辑门的组合
        - 如何根据真值表组合逻辑门
        - XOR(异或门)
        - MUX(多路复用器)
        
- 寄存器
    - 寄存器是什么
        - 寄存器的作用
    - 逻辑门与寄存器
        - D寄存器
        - AND-OR寄存器
        - JK触发器 选讲
    - 寄存器与I/O

- 内存
    - 怎样构建一块内存
    - 内存的种类
        - RAM
            - SRAM
            - DRAM
        - ROM
            - ROM
            - PROM/EPROM/EEPROM
            - Flash

- CPU
    - CPU的组成(简单的讲)
        - ALU(算术逻辑单元)
        - CU(控制单元)
            - 控制总线
            - 数据总线
            - 地址总线
        - 寄存器(不展开)
    - CPU指令集
        - 介绍指令集的意义
    - CPU的运行流程(重要,演示ADD命令的运行过程)

- MCU(用来演示程序运行)
    - 课堂演示
        - 演示寄存器控制输出(小灯泡)
        - 演示寄存器控制输入(按键读取)
        - 演示指令工作流程(现场debug观察程序运行)
    - 现场实操
        - 在面包板上搭建8051最小系统
        - 体验烧录程序



```mermaid
graph LR
    A[涵盖内容] --> B[CMOS-简单讲]
    B --> B1[什么是MOSFET]
    B --> B2[INV-非门:CMOS基本单元]

    A --> C[逻辑门-简单讲,留个印象]
    C --> C1[逻辑门是什么]
    C1 --> C1a[什么是真值表]
    C --> C2[CMOS与逻辑门]
    C2 --> C2a[NAND-与非门]
    C2 --> C2b[NOR-或非门]
    C2 --> C2c[AND-与门]
    C2 --> C2d[OR-或门]
    C --> C3[逻辑门的组合]
    C3 --> C3a[如何根据真值表组合逻辑门]
    C3 --> C3b[XOR-异或门]
    C3 --> C3c[MUX-多路复用器]

    A --> D[寄存器]
    D --> D1[寄存器是什么]
    D1 --> D1a[寄存器的作用]
    D --> D2[逻辑门与寄存器]
    D2 --> D2a[D寄存器]
    D2 --> D2b[AND-OR寄存器]
    D2 --> D2c[JK触发器-选讲]
    D --> D3[寄存器与I/O]

    A --> E[内存]
    E --> E1[怎样构建一块内存]
    E --> E2[内存的种类]
    E2 --> E2a[RAM]
    E2a --> E2a1[SRAM]
    E2a --> E2a2[DRAM]
    E2 --> E2b[ROM]
    E2b --> E2b1[ROM]
    E2b --> E2b2[PROM/EPROM/EEPROM]
    E2b --> E2b3[Flash]

    A --> F[CPU]
    F --> F1[CPU的组成-简单的讲]
    F1 --> F1a[ALU-算术逻辑单元]
    F1 --> F1b[CU-控制单元]
    F1b --> F1b1[控制总线]
    F1b --> F1b2[数据总线]
    F1b --> F1b3[地址总线]
    F1 --> F1c[寄存器-不展开]
    F --> F2[CPU指令集]
    F2 --> F2a[介绍指令集的意义]
    F --> F3[CPU的运行流程-重要,演示ADD命令的运行过程]

    A --> G[MCU-用来演示程序运行]
    G --> G1[课堂演示]
    G1 --> G1a[演示寄存器控制输出-小灯泡]
    G1 --> G1b[演示寄存器控制输入-按键读取]
    G1 --> G1c[演示指令工作流程-现场debug观察程序运行]
    G --> G2[现场实操]
    G2 --> G2a[在面包板上搭建8051最小系统]
    G2 --> G2b[体验烧录程序]

    classDef bigFont size:25px;
    class A,B,B1,B2,C,C1,C1a,C2,C2a,C2b,C2c,C2d,C3,C3a,C3b,C3c,D,D1,D1a,D2,D2a,D2b,D2c,D3,E,E1,E2,E2a,E2a1,E2a2,E2b,E2b1,E2b2,E2b3,F,F1,F1a,F1b,F1b1,F1b2,F1b3,F1c,F2,F2a,F3,G,G1,G1a,G1b,G1c,G2,G2a,G2b bigFont;
```


