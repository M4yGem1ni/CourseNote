#include<stdio.h>
#include<stdint.h>

int main()
{
    uint8_t uint8_num = 0xff;
    int8_t  int8_pnum = 1;
    int8_t int8_nnum = -128;
    for(uint8_t i=0;i<8;i++)
    {
        printf("left for %dbits\n",i);
        printf("uint8_num = %x\n",(uint8_t)(uint8_num<<i));
        printf("int8_pnum = %d\n",(int8_t)(int8_pnum<<i));
        printf("int8_nnum = %d\n\n",(int8_t)(int8_nnum<<i));
    }
    for(uint8_t i=0;i<8;i++)
    {
        printf("right for %dbits\n",i);
        printf("uint8_num = %x\n",(uint8_t)(uint8_num>>i));
        printf("int8_pnum = %d\n",(int8_t)(int8_pnum>>i));
        printf("int8_nnum = %d\n\n",(int8_t)(int8_nnum>>i));
    }
}