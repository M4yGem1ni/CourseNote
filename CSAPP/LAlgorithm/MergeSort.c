#include <stdio.h>
#include <stdlib.h>

/**
 * @brief   这是一个简单的归并排序算法的示意,时间复杂度为O(N*logN)
 * @brief   闲的没事干再加了个class进去
 */

typedef struct MergeClassDef
{
    int*    Sort;
    int     Length;
    void    (*MergeStep)(struct MergeClassDef*,int,int);
    void    (*MergeRec)(struct MergeClassDef*,int,int);
    void    (*MergeOutput)(struct MergeClassDef*);
    void    (*MergeClassDeinit)(struct MergeClassDef*);
}MergeClass;

void MergeFunc(MergeClass* Merge,int start,int end)
{
    int middle = (start+end)/2;
    int L = middle-start+1,R = end-middle;
    int Larray[L],Rarray[R];
    int i,j;
    for(i=0;i<L;i++)
    {
        Larray[i] = Merge->Sort[start+i];
    }
    for(j=0;j<R;j++){
        Rarray[j] = Merge->Sort[middle+j+1];
    }
    i=j=0;
    while(i<L && j<R){
        if(Larray[i]>Rarray[j]){
            Merge->Sort[start+i+j] = Rarray[j];
            j++;
        }
        else
        {
            Merge->Sort[start+i+j] = Larray[i];
            i++;
        }
    }
    if(i>=L && j<R){
        for(;j<R;j++){
            Merge->Sort[start+i+j] = Rarray[j];
        }
    }
    else if(j>=R && i<L){
        for(;i<L;i++){
            Merge->Sort[start+i+j] = Larray[i];
        }
    }
}

void MergeRecFunc(MergeClass* Merge,int start,int end)
{
    int m = (start+end)/2;
    if(start<end){
        MergeRecFunc(Merge,start,m);
        MergeRecFunc(Merge,m+1,end);
        MergeFunc(Merge,start,end);
    }
}

void MergeOutputFuc(MergeClass* Merge)
{
    Merge->MergeRec(Merge,0,Merge->Length-1);
    printf("\nMerge Output :\n");
    for(int i=0;i<Merge->Length;i++){
        printf("%d ",Merge->Sort[i]);
    }
    printf("\n");
}

void MergeClassDeinitFuc(MergeClass* Merge)
{
    free(Merge->Sort);
    free(Merge);
    printf("\nMergeDeinit OK\n");
}

void MergeClassInit(MergeClass* Merge,int*Sort,int Length)
{
    Merge->Length = Length;
    Merge->Sort = (int*)malloc(sizeof(int)*Length);
    for(int i=0;i<Length;i++){
        (Merge->Sort)[i] = Sort[i];
    }
    Merge->MergeStep = MergeFunc;
    Merge->MergeRec = MergeRecFunc;
    Merge->MergeOutput = MergeOutputFuc;
    Merge->MergeClassDeinit = MergeClassDeinitFuc;
}

int main()
{
    int Sort[] = {12,14,12,45,31,2,13,17};
    MergeClass* SortValue = (MergeClass*)malloc(sizeof(MergeClass));
    MergeClassInit(SortValue,Sort,8);
    printf("Orignal Type:\n");
    for(int i=0;i<sizeof(Sort)/sizeof(int);i++){
        printf("%d ",Sort[i]);
    }
    SortValue->MergeOutput(SortValue);
    SortValue->MergeClassDeinit(SortValue);
}
