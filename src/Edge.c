#include "Edge.h"
#include <stdio.h>
#include <stdlib.h>

Edge Kruskal(Edge G)
{
    Edge MinTree = malloc(sizeof(_Edge));
    MinTree_Init(G, MinTree);

    DisjSet S;
    DisjSet_Init(S);

    SetType Uset, Vset;
    // You can also use heap sort
    qsort(G->Edge,G->Edge_Num,sizeof(G->Edge[0]),Compare);

    for(int i = 0; i < G->Edge_Num; i++)
    {
        /*
        * The function of the union check is to confirm 
        * whether the vertices are in the same subtree, 
        * and merge if not.
        */
        Uset = Find(G->Edge[i].inital,S);
        Vset = Find(G->Edge[i].end,S);
        if(Uset != Vset)
        {
            MinTree->Edge[MinTree->Edge_Num++] = G->Edge[i];
            Union(S,Uset,Vset);
        }
        if(MinTree->Edge_Num ==G->Vertex_Num-1) break;
    }
    return MinTree;
}
// Use to qsort() in the C built-in functions
static int Compare(const void *inital, const void *end)
{
    return ((_edge*)inital)->weight - ((_edge*)end)->weight;
}

Edge Edge_Init()
{
    Edge G = malloc(sizeof(_Edge));
    printf("Please input vertex number and arc number,such as (2,1)\n");
    scanf("%d,%d",&G->Vertex_Num,&G->Edge_Num);

    printf("Please input %d arc,such as (1,2,1)\n", G->Edge_Num);
    for(int i=0;i<G->Edge_Num;i++)
      scanf("%d,%d,%d",&G->Edge[i].inital,&G->Edge[i].end,&G->Edge[i].weight);

    return G;
}

// A utility function to find set of an element X
// (uses path compression technique)
static SetType Find(DisjSet_ElementType X,DisjSet S)
{
    if(S[X]<=0) return X;
    else return S[X]=Find(S[X],S);
}

// A function that does union of two sets of Root1 and Root2
// (uses union by size)
static void Union(DisjSet S,SetType Root1,SetType Root2)
{
    if(S[Root2]<S[Root1])//Root2 is deeper Set
      S[Root1] = Root2; //Make Root2 new root 
    else
    {
        if(S[Root1]==S[Root2]) //Same height
           S[Root1]--; //Update Height
        S[Root2] = Root1;
    }
}

static void DisjSet_Init(DisjSet S)
{
    for(int i = 1; i <= NumSets; i++)
       S[i] = -1;
}

static void MinTree_Init(Edge G, Edge MinTree)
{
    MinTree->Vertex_Num = G->Vertex_Num;
    MinTree->Edge_Num = 0;
}

void Edge_Print(Edge MinTree)
{
    for(int i = 0; i <MinTree->Edge_Num; i++)
     printf("%d->%d weight:%d\n", MinTree->Edge[i].inital, MinTree->Edge[i].end,
      MinTree->Edge[i].weight);
}