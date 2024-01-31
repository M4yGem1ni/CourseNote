# L02: The Digital Abstraction
### what makes a good bit?
- cheap,small(we have a large demand)
- stable(reliable,repeatable)
- ease of manipulation
```
什么是好比特?
价格便宜，体积小(我们有很大的需求)
稳定(可靠，可重复)
易于操作
```
--------------------
### why choose voltage to encode message
pros:
- easy generation, detection
- lot of engineering knowledge
- potentially ***zero*** power in steady state

cons:
- **easily affected by environment**
- electric wires required
- take time to change
```
为什么选择电压编码:

优点:
易于生成
具有大量的工程知识
在稳态下潜在零功率

缺点:
易受环境影响
需要电线
改变需要时间
```
------------------------
## use voltages digitally
we attempt to encode only 1 bit of infomation: "0" and "1".In another word, **we are using voltages digitally**.

1. we use **a single standard** to divide votages into two parts,like 0.5V,if we get 4.999V, we call it "0" and we get 5.001V, we refer it as "1".
![L02_attempt1](/Image/L02_attempt1.png)
Obviously, it will make Mr. computer confused because he cannot distinguish precisely between 4.999V and 5.001V. So this way is **False**
2. So we can make two standards, called $V_H$ and and $V_L$ and like *attempt_1*, but we divide it into 3 parts.If $V$ are less than $V_L$ ,we call it "0",and if $V$ are higher than $V_H$, we name it "1".
![L02_attempt2](/Image/L02_attempt2.png)
what if $V$ is between $V_L$ and $V_H$ ? Just forget it,because it is forbidden.
```
我们用电压编码1位信息:“0”和“1”。换句话说，我们可以将电压正在数字化。
1.我们用一个标准把电压分成两部分，比如0.5V，如果我们得到4.999V，
  我们称之为“0”，如果我们得到5.001V，我们称之为“1”。显然，这会使计算
  机先生感到困惑，因为他不能准确地区分4.99 v和5.001V。所以这个方向是
  不正确的
2. 我们可以制定两个标准，分别是V_H和V_L。像attempt_1，但是我们把
   分成3部分。如果V小于V_L，我们称之为“0”，如果V大于V_H，我们称之为
   “1”。
   如果V在V_L和V_H之间呢?忘了它吧，因为这是被禁止的。
```
--------------------
## Digital Processing Element

### Static Discipline
- one or more than one digital inputs.
- one or more than one digital outputs.
- a functional specification that details the value of each output for every possible combination of valid input values
- a timing specification consisting(at mininum) of an upper bound $t_{PD}$ on the required time for the device to compute the specified output values from an arbitrary set of stable, valid input values. 
```
静态的规则
一个或多个数字输入。
一个或多个数字输出。
详细说明有效输入值的每种可能组合的每个输出值的功能规范.
一种时序规范，(至少)由设备从一组稳定有效的输入值中计算出指定输出值所需时间的t_PD上界组成。
```
  
### Combinational Digital System
A set of interconnected elements is a combinational device if they obey these rules.
- each circuit elements is combinational
- every input is connected to exactly one output or to some vast supply of constant 0's and 1's.
- the circuit contains no directed cycles.
```
组合数字系统
如果一组相互连接的元素遵守这些规则，那么它们就是一个组合系统。
1. 每个电路元件都是组合的
2. 每个输入都连接到一个输出，或者连接到大量的常数0和1。
3. 电路不包含有死循环。
```

### Input and Output
#### Different Votages:
The Votages of Input and Output are **different**:

$V_{OL}$ < $V_{IL}$  $while$  $V_{OH}$ > $V_{IH}$
![L02_InputAndOutput](/Image/L02_InputAndOutput.png)

This because the **output** must be ***preciser*** than the **input** to reduce the influence of **noise**.
```
这是因为输出必须比输入精确，以减少噪声的影响。
```

#### noise margin

The range ($V_{OL}$,$V_{IL}$) and ($V_{IH}$,$V_{OH}$) is called **noise margin**
```
(V_OL,V_IL)和(V_IH,V_OH) 是 噪声容限
```
![L02_noise_margrins](/Image/L02_noise_margrins.png)

### Buffer
![L02_Buffer1](/Image/L02_Buffer1.png)
It has a single Input and a single Output. And after some small propagation **delay**, the output has the **same** value as the input.
```
它有一个输入和一个输出。经过一些小的传播延迟后，输出与输入具有相同的值。
```

![L02_Buffer](/Image/L02_Buffer.png)
Accroading to **Input and Output** I refered before. Device will never fall a point on the pink rigion.
```
根据我之前提到的输入和输出。设备永远不会落在粉红色区域上。
```

**So here comes the relationship between $V_{out}$ and $V_{in}$**
```
这就是V_out和V_in之间的关系。
```
![L02_Buffer2](/Image/L02_Buffer2.png)
And devices don't behave themselves **at the middle**.
![L02_Buffer3](/Image/L02_Buffer3.png)