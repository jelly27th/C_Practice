#include "Graph.h"
#include <stdlib.h>
#include <stdio.h>

/*
-----    -----
| 1 | -> | 2 |
-----    -----
  |   \   /|\
 \ /  _\/  |
-----    ----- 
| 4 |    | 3 |
-----    -----
 / \  \     |
  |   _\/  \|/
-----     -----  
| 6 | ->  | 5 |
-----     -----  
*/
void Topological_Sort(Graph G)
{
    /*
    * Create an array of in-degrees for each vertex
    * and statistics
    * Note: if your camke project build in VS, you should
    * use int indegree[10] replace int indegree[G->Vertex_Num]
    * otherwise it will fail build
    */
    int indegree[10];
    // int indegree[G->Vertex_Num];
    FindIndegree(G, indegree);
    
    // Init stack
    Stack S = Stack_Init();
    
    // Find vertex for zero indegree and push it onto the stack
    for(int i = 0; i < G->Vertex_Num; i++)
    {
        if(!indegree[i]) Push(S, i);
    }

    int index,count = 0;
    while(!Stack_IsEmpty(S))
    {
        index = Pop(S);
        printf("%d ",G->Vertices[index].Data);
        ++count;
        
        for(Arc_Node p = G->Vertices[index].First_Adj; p!=NULL; p = p->Arc_Next)
        {
            vertex_type k = p->Adj_Index;
            if(!(--indegree[k])) Push(S,k);
        }
    }
    // Free stack
    free(S);

    if(count<G->Vertex_Num) 
      printf("该图有回路\n");
}
// Find the vertex corresponding to the position index in the adjacency list array
static int Locate_Vertex(Graph G, vertex_type vertex)
{
    for(int i=0; i<G->Vertex_Num; ++i)
    {
        if(G->Vertices[i].Data == vertex)
          return i;
    }
    return -1;
}
// Init stack and remember free stack
static Stack  Stack_Init()
{
    Stack S = malloc(sizeof(_Stack));
    S->Next = NULL;
    return S;
}

static bool Stack_IsEmpty(Stack S)
{
    if(S->Next == NULL) return true;
    return false;
}

static void Push(Stack S, vertex_type vertex)
{
    Stack P = malloc(sizeof(_Stack));
    P->Data = vertex;
    P->Next = S->Next;
    S->Next = P;
}

static vertex_type Pop(Stack S)
{
    Stack tmp = S->Next;
    vertex_type vertex = tmp->Data;
    S->Next = tmp->Next;
    free(tmp);
    return vertex;
}

static void FindIndegree(Graph G, int indegree[])
{
    // Init indegree array
    for(int i = 0; i < G->Vertex_Num; i++)
     indegree[i] = 0;
    
    // Traverse the adjacency list 
    // and calculate the degree of the vertex set
    Arc_Node P;
    for(int i = 0, j; i < G->Vertex_Num; i++)
    {
        P = G->Vertices[i].First_Adj;
        while(P!= NULL)
        {
            indegree[P->Adj_Index]++;
            P = P->Arc_Next;
        }
    }
}
//  Create AOV network and build adjacency list
Graph CreateAOV()
{
    Graph G = malloc(sizeof(_Graph));
    printf("Please input vertex number and arc number,such as (2,1)\n");
    scanf("%d,%d", &G->Vertex_Num,&G->Arc_Num);

    printf("Please input %d vertex,such as 1 2 3...\n", G->Vertex_Num); 
    for(int i = 0; i < G->Vertex_Num;i++)
    {
        scanf("%d",&G->Vertices[i].Data);
        G->Vertices[i].First_Adj = NULL;
    }

    printf("Please input %d arc,such as (1,2)\n", G->Arc_Num);
    vertex_type start, end;
    for(int i = 0, locate; i < G->Arc_Num; i++)
    {
        scanf("%d,%d",&start,&end);
        Arc_Node P = malloc(sizeof(_Arc_Node));
        P->Adj_Index = Locate_Vertex(G,end);
        locate = Locate_Vertex(G,start);
        P->Arc_Next = G->Vertices[locate].First_Adj;
        G->Vertices[locate].First_Adj = P;
    } 
    return G;
}

void Graph_Delete(Graph G)
{
    free(G);
}

void Tarjan1(Graph G, int u, int DFN[], int LOW[], Stack S, bool stack[])
{
    static int index = 0;

    DFN[u] = LOW[u] = ++index;
    Push(S,u);
    stack[u] = true;

    int v;
    for(Arc_Node arc = G->Vertices[u].First_Adj;  arc != NULL; arc = arc->Arc_Next)
    {
        v = arc->Adj_Index;
        if(DFN[v] == NIL)
        {
            Tarjan1(G, v, DFN, LOW, S, stack);
            LOW[u] = MIN(LOW[u], LOW[v]); 
        }
        else if(stack[v] == true)
          LOW[u] = MIN(LOW[u], DFN[v]);
    }

    if(DFN[u]==LOW[u])
    {
        int w = NIL;
        do{
            w = Pop(S);
            stack[w] = false;
            printf("%d ", G->Vertices[w].Data);
        }while(w != u);
        printf("\n");
    }
}

void Tarjan(Graph G)
{
    /* 
    * Note: if your camke project build in VS, you should
    * use int n = 6 replace int n = G->Vertex_Num
    * otherwise it will fail build
    */
    int n = G->Vertex_Num;
    int DFN[n],LOW[n];
    bool stack[n];
    Stack S = Stack_Init();

    for(int i = 0; i < n; i++)
    {
        DFN[i] = LOW[i] = NIL;
        stack[i] = false;
    }

    for(int i = 0; i < n; i++)
      if(DFN[i] == NIL) 
        Tarjan1(G, i, DFN, LOW, S, stack);
}

static vertex_type Top(Stack S)
{
    return S->Data;
}