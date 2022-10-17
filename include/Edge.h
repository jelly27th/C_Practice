#ifndef _EDGE_H
#define _EDGE_H

#define MAX_EDGE_NUM (11)
typedef int vertex_Type;
typedef struct edge{
    // Two vertices between edges
    vertex_Type inital;
    vertex_Type end;
    int weight; //Weight of the edge
}_edge;
typedef _edge edge[MAX_EDGE_NUM];
typedef struct _Edge{
    int Vertex_Num; 
    int Edge_Num;
    edge Edge;
}_Edge, *Edge;

Edge Kruskal(Edge G);
Edge Edge_Init();
void Edge_Print(Edge MinTree);
static int Compare(const void *inital, const void *end);

#define NumSets (10)
typedef int DisjSet[NumSets+1];
typedef int SetType;
typedef int DisjSet_ElementType;

static void MinTree_Init(Edge G, Edge MinTree);
static void DisjSet_Init(DisjSet S);
static void Union(DisjSet S,SetType Root1,SetType Root2);
static SetType Find(DisjSet_ElementType X,DisjSet S);

#endif