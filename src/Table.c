/**
 * @file Table.c
 * @author Jelly (wugd827@163.com)
 * @brief excrise 9.9,I choose Dijkstra's algorithm to slove
 *        But other shortest path algorithms are roughly similar, probably
 * @version 0.1
 * @date 2022-10-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "Table.h"
#include <stdlib.h>
#include <stdio.h>

/*   
                         -----      2       -----           
                         | 1 |  --------->  | 2 |
                         ------             -----
                        __    \ 1          3/    \ 10
                       4 /\    \           /      \
                        /      _\/       \/_      _\/ 
                      -----    2  -------      2   -----    
                      | 3 | <-----|  4  |  ------->| 5 |
                      -----       -------          -----
                        \          /   \             /
                      5  \      8 /     \ 4         / 6
                         _\/    \/_     _\/       \/_
                           -----      1    -----                       
                           | 6 |   <-------| 7 |
                           -----           -----
*/
void Dijkstra(Table T)
{   
    for(int Cur_Index= SmallDistance(T);Cur_Index != NotVertex; 
        Cur_Index= SmallDistance(T))
    {
        T[Cur_Index].Known = true;
        int Com_Index;//Compare the distance of vertex between the adjacency list
        for(List P = T[Cur_Index].Header; P != NULL; P = P->Next)
        {
            Com_Index = Find_Index(T,P->Data);
            if(!T[Com_Index].Known)
            {
                if(T[Cur_Index].Distance+P->Weight<T[Com_Index].Distance)
                {
                    T[Com_Index].Distance = T[Cur_Index].Distance + P->Weight;
                    T[Com_Index].Path = Cur_Index;
                }
            }
        }
    }
}
// Find index of smallest distance  unmarked vertex 
static int SmallDistance(Table T)
{
    int min = NotVertex, dis = Infinity;
    for(int i = 0; i < NumVertex; i++)
    {
        if(!T[i].Known)
        {
            if(T[i].Distance < dis)
            {
                min = i;
                dis = T[i].Distance;
            }
        }
    }
    return min;
}

static int Find_Index(Table T, Vertex_Type vertex)
{
    for(int i = 0; i < NumVertex; i++)
    {
        if(T[i].Data == vertex)
        return i;
    }
    return -1;
}

void Table_Init(Vertex_Type vertex,Table T)
{
    Creat_Table(T);
    int i;
    for(i= 0; i < NumVertex; i++)
    {
        T[i].Known = false;
        T[i].Distance = Infinity;
        T[i].Path = NotVertex;
    }
    i = Find_Index(T, vertex);
    T[i].Distance = 0;
}

static void Creat_Table(Table T)
{
    printf("Please input vertex number and arc number,such as (2,1)\n");
    int Vertex_Num,Arc_Num;
    scanf("%d,%d", &Vertex_Num,&Arc_Num);

    printf("Please input %d vertex\n", Vertex_Num);
    for(int i=0; i<Vertex_Num; i++)
    {
        T[i].Data = i+1;
        T[i].Header = NULL;
    } 

    printf("Please input %d arc,such as (1,2,1)\n", Arc_Num);
    Vertex_Type start, end;
    int Weight,index;
    for (int i = 0; i < Arc_Num; i++)
    {
        scanf("%d,%d,%d",&start,&end,&Weight);
        List P = malloc(sizeof(Node));
        P->Data = end;
        P->Weight = Weight;
        index = Find_Index(T,start);
        P->Next = T[index].Header;
        T[index].Header = P;
    }
}

void Print_Table(Table T, Vertex_Type vertex)
{
    int index = Find_Index(T,vertex);
    if(T[index].Path!=NotVertex)
    {
        int i = T[index].Path;
        Print_Table(T,T[i].Data);
        printf("-->");
    }
    printf("%d",vertex);
}