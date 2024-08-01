#include <stdio.h>
#include <stdlib.h>

typedef struct DijkstraClassDef
{
    int     Mininum;
    int*    WayPointData;
    int     Size;
    int**   Map;
    // int*    Routine;
    void    (*DijkstraClassDeinit)(struct DijkstraClassDef*);
}DijkstraClass;

/**
 * @brief Dijkstra类型取消初始化
 */
void DijkstraClassDeinitFuc(DijkstraClass* Dijkstra)
{
    for(int i=0;i<Dijkstra->Size;i++){
        free(Dijkstra->Map[i]);
    }
    free(Dijkstra->WayPointData);
    free(Dijkstra);
}

/**
 * @brief Dijkstra类型初始化
 */
void DijkstraClassInit(DijkstraClass* Dijkstra,int** Map,int Size)
{
    Dijkstra->Mininum = 0;

    Dijkstra->WayPointData = (int*)malloc(sizeof(int)*Size);
    for(int i=0;i<Size;i++){
        Dijkstra->WayPointData[i] = 0;
    }

    Dijkstra->Size = Size;

    Dijkstra->Map = (int**)malloc(sizeof(int*)*Size);
    for(int i=0;i<Size;i++){
        Dijkstra->Map[i] = (int*)malloc(sizeof(int)*Size);
        for(int j=0;j<Size;j++){
            Dijkstra->Map[i][j] = Map[i][j];
        }
    }

}

int main()
{
    int Road[5][5] = {{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1}};
}