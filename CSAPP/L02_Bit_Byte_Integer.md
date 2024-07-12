# L02_Bit_Byte_Integer.md
## 注意事项:

1. 补码原理:
    **unsigned char**
    |数\权重|$2^3$|$2^2$|$2^1$|$2^0$|
    |:---:|:---:|:---:|:---:|:---:|
    |15|1|1|1|1|
    |10|1|0|1|0|
    |2|0|0|1|0|

    $w = 4bit$
    $N = \displaystyle \sum^{w-1}_{i=0}b_i*2^i$

    **signed char**
    |数\权重|-$2^3$|$2^2$|$2^1$|$2^0$|
    |:---:|:---:|:---:|:---:|:---:|
    |-1|1|1|1|1|
    |-5|1|0|1|1|
    |-8|1|0|0|0|
    |2|0|0|1|0|

    $w = 4bit$
    $N = -2^{w-1}+\displaystyle \sum^{w-2}_{i=0}b_i*2^i$

2. 编程注意事项
    **无符号整型作为index**
    ```c
    #include <stdio.h>
    #define NUM 5
    unsigned int i;
    int a[NUM];
    void main()
    {
        for (i = NUM-1;i>=0;i--)
        {
            a[i] = a[i]*a[i];
        }
    }
    ```
    在这段程序中,由于i为负值时才能退出程序,但是对于unsigned char来说并不存在负数0-1 = MAXI,所以这个程序不会停止.

    **sizeof()的强制类型转换**
    ```c
    for(int i = n - 1; i - sizeof(char) >= 0; i--);
    ```
    sizeof会返回一个无符号整型,i和一个无符号整型进行运算时,会强制类型转换为一个无符号整型,所以他们这一整体永远不会小于0,这行代码将会一直执行卡去

3. 常见操作
    1. 指针状态监测
        ```c
        if(p && *p){
            fun();
        }
        ```
        确保p不是空指针且p指向的位置不是空。

    2. 符号位扩展
        ```c
        #include <stdio.h>
        #include <stdint.h>
        /**
        * @b 将a扩展为16位的b,保持符号不变
        */

        void main()
        {
            int8_t a = -127;    //  0x80
            int16_t b = 0;    //  0x0000
            //your code type here
                (a&0x80) && (b|=0xff00);
                b|=a;
            //end
            printf("b = %d",b);
        }
        ```

## 如何使用unsigned类型进行向下遍历
在有些时候,我们需要使用unsigned类型的的index进行遍历,正如上面提到的int和uint之间的转换出现的问题(sizeof强制类型转换),我们需要建立一定的标准防止错误出现.
如我们需要计数时代码最好这样写
```c
uint8_t i;
for(i=cnt-2;i<cnt;i--){
    a[i] = a[i+1];
}
```
cnt位数组a的长度,i从cnt-2开始遍历到0,然后溢出到0xff,结束循环这样既**防止了无限循环**,也保证了数组**下标不会越界**
当然还有更好地改写方法
```c
size_t i;
for(i=cnt-2;i<cnt;i--){
    a[i] = a[i+1];
}
```
这样做的好处在于size_t的数据类型是**unsigned long**,可以保证i越界之后的数字一定大于等于cnt,永远不会陷入无限循环
