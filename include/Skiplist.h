#ifndef _SKIPLIST_H
#define _SKIPLIST_H
#include <stdbool.h>

#define MAX_LEVEL (16) // Maximum number of layers

typedef struct _Skiplist_Node {
    int Data; // Node data
    int Level; // Total layers of nodes
    // Advance array.
    // Elements index: 0~Level
    struct _Skiplist_Node* Next[MAX_LEVEL]; 
}_Skiplist_Node, *Skiplist_Node;

typedef struct {
    int Num; // Number of nodes
    int Level; // Maximum layer
    // Head node: not data nodes and max layer
    Skiplist_Node Head;
}_Skiplist, *Skiplist;

static int RandLevel();
Skiplist_Node Skiplist_NewNode(int Data, int Level);
void Skiplist_FreeNode(Skiplist_Node Node);
Skiplist Skiplist_Generate();
void Skiplist_Free(Skiplist S);
void Skiplist_Insert(Skiplist S, int Data);
static bool Skiplist_IsHas(Skiplist S, int Data);
bool Skiplist_Delete(Skiplist S, int Data);
int Skiplist_Find_Header(Skiplist S);  
int Skiplist_Delete_Header(Skiplist S);
static int Len(Skiplist S);
void Skiplist_Print(Skiplist S);

#endif