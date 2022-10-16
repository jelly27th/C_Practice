#ifndef _TABLE_H
#define _TABLE_H
#include <stdbool.h>

#define Infinity (65535)
#define NotVertex (-1)
#define NumVertex (7)
typedef int Vertex_Type;
typedef int Distance_Type;
typedef struct Node{
    Vertex_Type Data;
    int Weight;
    struct Node* Next;
}Node,*List;
struct Table{
    List Header;
    int Known;
    Distance_Type Distance;
    int Path;
    Vertex_Type Data;
};
typedef struct Table Table[NumVertex];

void Table_Init(Vertex_Type V,Table T);
void Dijkstra(Table T);
static int SmallDistance(Table T);
static int Find_Index(Table T, Vertex_Type vertex);
static void Creat_Table(Table T);
void Print_Table(Table T, Vertex_Type vertex);

#endif