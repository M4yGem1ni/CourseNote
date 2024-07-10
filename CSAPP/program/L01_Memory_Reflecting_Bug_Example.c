#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#if defined(__linux__)
#define SIGBREAK 0x00
#endif
/**
 *@example 内存越界的相关示例
**/

void handle_signal(int signal) {
    if (signal == SIGABRT||signal == SIGINT||signal == SIGFPE||signal == SIGSEGV||signal == SIGTERM||signal == SIGBREAK) 
    {
        char string[6][10] = {"SIGABRT","SIGINT","SIGFPE","SIGSEGV","SIGTERM","SIGBREAK"};
        if(signal == SIGABRT){printf("FATAL:%s\n",string[0]);}
        else if(signal == SIGINT){printf("FATAL:%s\n",string[1]);}
        else if(signal == SIGFPE){printf("FATAL:%s\n",string[2]);}
        else if(signal == SIGSEGV){printf("FATAL:%s\n",string[3]);}
        else if(signal == SIGTERM){printf("FATAL:%s\n",string[4]);}
        else if(signal == SIGBREAK){printf("FATAL:%s\n",string[5]);}
        printf("Segmentation fault caught!\n");
        system("echo 'Executing custom command after segmentation fault'");
        exit(1);   
    }
}

typedef struct 
{
    int a[2];
    double d;
}struct_t;

double fun(int i)
{
    volatile struct_t s;
    s.d = 3.14;
    s.a[i] = 1073741824;
    return s.d;
}

int main()
{
    signal(SIGSEGV, handle_signal);
    for(int i=0;i<256;i++)
    {
        
        printf("Index:%d\n",i+1);
        printf("%f\n",fun(i));
        getchar();
    }
    return 0;
}
