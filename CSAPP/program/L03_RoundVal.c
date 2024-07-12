#include <stdio.h>
#include <stdint.h>

int main()
{
    int8_t Nnum = -5;
    int8_t Pnum = 7;
    int8_t div  = 2;
    printf("Nnum = %d\nPnum = %d\ndiv  = %d\n",Nnum,Pnum,div);
    printf("Nnum/div = %d\n",Nnum/div);
    printf("Pnum/div = %d\n",Pnum/div);
    return 0;
}