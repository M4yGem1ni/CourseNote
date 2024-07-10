#include <stdio.h>
#include <stdint.h>
/**
 * @b 使用基础运算的方法返回一个b使得b=a
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
