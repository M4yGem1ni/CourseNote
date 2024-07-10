#include <stdio.h>
#include <stdlib.h>
int main()
{
    double a = 1e23;
    double b = 1e-11;
    printf("a = %e\nb = %e\n",a,b);
    printf("a+b = %e\n",a+b);
}