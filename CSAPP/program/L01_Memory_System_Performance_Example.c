#include <stdio.h>
#include <time.h>

int main() {
    clock_t start, end;
    int i = 0,j = 0;
    
    char Array1[100][1000] = {0};
    char Array2[100][1000] = {0};
    
    double cpu_time_used;

    start = clock();

    for (i = 0; i < 100; i++)
    {
        printf("%d\n",i);
        for(j = 0;j <1000;j++)
        {
            Array1[i][j] = Array2[i][j];
        }
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("time:%fs\n", cpu_time_used);

    return 0;
}
