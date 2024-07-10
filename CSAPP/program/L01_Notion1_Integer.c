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