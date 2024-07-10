# L01_Course_Overview
## Notion1: Ints are not Integers,Float are not Real
1. 对于整型数据来说,存在计算越界的情况不能反应真实的计算结果
    [程序源码](#Notion1:Int)
    <span id="Notion1:Int_t"></span>
    **bash**
    ``` bash
    a = 10,b = 9,c = 8
    a*b = 90
    a*b*c = 208
    b*c*a = 208
    c*a*b = 208
    ```
    在这个示例中,我们定义了a,b,c三个8位无符号整型数据(0-255),在计算时,发现a\*b\*c的真实值和计算得到的值不相符(720 != 208)
    但是计算**仍满足乘法交换律和乘法结合律**.


2. 对于浮点型数据来说,一个极大的数会吞并比它小很多的数
    
    [程序源码](#Notion1:Float)
    <span id="Notion1:Float_t"></span>
    **bash**
    ```bash
    a = 1.000000e+023
    b = 1.000000e-011
    a+b = 1.000000e+023
    ```
    在此次加法运算中,a远大于b造成了在加法运算后a吞并了b


<span id="Notion1:Int">Notion1:Int</span>
``` c
#include <stdio.h>
#include <stdlib.h>
typedef unsigned char uint8_t;
int main()
{
    uint8_t a = 10;
    uint8_t b = 9;
    uint8_t c = 8;
    uint8_t d;
    printf("a = %d,b = %d,c = %d\n",a,b,c);
    d = a*b;
    printf("a*b = %d\n",d);
    d = a*b*c;
    printf("a*b*c = %d\n",d);
    d = b*c*a;
    printf("b*c*a = %d\n",d);
    d = c*a*b;
    printf("c*a*b = %d\n",d);
}
```
[返回文档](#Notion1:Int_t)

<span id="Notion1:Float">Notion1:Float</span>
```c
int main()
{
    double a = 1e23;
    double b = 1e-11;
    printf("a = %e\nb = %e\n",a,b);
    printf("a+b = %e\n",a+b);
}
```
[返回文档](#Notion1:Float_t)