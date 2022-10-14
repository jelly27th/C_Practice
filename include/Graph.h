#ifndef _GRAPH_H
#define _GRAPH_H
#include <stdbool.h>

#define MAX_VERTEX_MAX (20) // max vertex number
typedef int vertex_type;
typedef struct Arc_Node{
    int Adj_Index;//The position index of the adjacency list in the array
    struct Arc_Node* Arc_Next; 
}_Arc_Node, *Arc_Node;
typedef struct Vertex_Node{
    vertex_type Data;//vertex data field
    Arc_Node First_Adj;
}Vertex_Node;
typedef Vertex_Node Adj_List[MAX_VERTEX_MAX];//Build adjacency list
typedef struct _Graph{
    Adj_List Vertices;//Array of vertices and each adjacency list in the graph
    int Vertex_Num;//Number of vertices
    int Arc_Num;//Number of arc edges
}_Graph,*Graph;

void Topological_Sort(Graph G);
static int Locate_Vertex(Graph G, vertex_type vertex);

typedef struct _Stack{
    vertex_type Data;
    struct _Stack* Next;
}_Stack,*Stack;

static Stack Stack_Init();
static bool Stack_IsEmpty(Stack S);
static void Push(Stack S, vertex_type vertex);
static vertex_type Pop(Stack S);
static void FindIndegree(Graph G, int indegree[]);
Graph CreateAOV();
void Graph_Delete(Graph G);

#endif