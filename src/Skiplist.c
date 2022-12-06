#include <stdio.h>
#include <stdlib.h>
#include "Skiplist.h"
#include "Rand.h"

// generate a random level between 1 and MAX_LEVEL
// Note: it has a problem, it can't break out of the loop. 
static int RandLevel() {
    int level = 1;
    // increment level with probability P.
    // P = 1/2, level = 1.
    // P = 1/4, level = 2.
    // P = 1/8, level = 3.
    // P = 1/(2^n), level = n.
    // max level  is MAX_LEVEL.
    while ((rand() & 65535) * 1.0 / 65535 < 0.5) {
        level++; 
        printf("%d\n", level);
    }
    return level < MAX_LEVEL ? level : MAX_LEVEL;
}

// Create a new node
Skiplist_Node Skiplist_NewNode(int Data, int Level) {
    Skiplist_Node node = malloc(sizeof(_Skiplist_Node));
    if (node != NULL) {
        node->Data = Data;
        node->Level = Level;
        for (int i = 0; i < MAX_LEVEL; i++) {
            node->Next[i] = NULL;
        }
    }
    return node;
}

// Free a node
void Skiplist_FreeNode(Skiplist_Node Node) {
    if (Node != NULL) free(Node);
}

// Create a new skiplist
Skiplist Skiplist_Generate() {
    Skiplist S = malloc(sizeof(_Skiplist));
    if (S != NULL) {
        S->Head = Skiplist_NewNode(-1, 1);
        S->Level = 1;
        S->Num = 0;
    }
    return S;
}

// Free a skiplist
void Skiplist_Free(Skiplist S) {
    if (S != NULL) {
        while (S->Level > 1) Skiplist_Delete_Header(S);
        Skiplist_FreeNode(S->Head);
        free(S);
    }
}

// Insert a new element node
void Skiplist_Insert(Skiplist S, int Data) {
    /* First step: find the insertion position of each layer */

    // last[i]: The predecessor node of the insertion position at level i
    Skiplist_Node last[MAX_LEVEL];
    Skiplist_Node pos = S->Head;

    for (int i = S->Level - 1; i >= 0; i--) {
        while (pos->Next[i] != NULL && pos->Next[i]->Data < Data)
            pos = pos->Next[i];
        last[i] = pos;
    }

    /*Second step: generate new nodes and layers*/
    // int level = RandLevel(); // The number of layers of the new node
    int level = RandInt(1, 16);

    // if number of layers of the new node is larger than 
    // layers of the original node.
    // It is necessary to supplement the high bits of the last array,
    // and the head will point to this node
    if (level > S->Level) {
        for (int i = S->Level; i < level; i++)
            last[i] = S->Head;
        S->Level = level;
    }

    /*Third step: each layer performs insertion*/
    Skiplist_Node Node  = Skiplist_NewNode(Data, level);
    for (int i = 0; i < level; i++) {
        Node->Next[i] = last[i]->Next[i];
        last[i]->Next[i] = Node;
    }

    // Update number of nodes
    S->Num++;
}

// Return whether Data is in the skip list.
// Actually find data in the skip list
static bool Skiplist_IsHas(Skiplist S, int Data) {
    Skiplist_Node pos = S->Head;
    for (int i = S->Level - 1; i >= 0; i--) {
        while (pos->Next[i] != NULL && pos->Next[i]->Data < Data)
            pos = pos->Next[i];
    }
    pos = pos->Next[0];
    return pos != NULL && pos->Data == Data;
}

// Delete one node from the skip list 
bool Skiplist_Delete(Skiplist S, int Data) {
    /* First step: Find the predecessor node of 
    *  the deletion position of each layer.
    */
   Skiplist_Node last[MAX_LEVEL];
   Skiplist_Node pos =S->Head;
   for (int i = S->Level - 1; i >= 0; i--) {
        while (pos->Next[i] != NULL && pos->Next[i]->Data < Data)
            pos = pos->Next[i];
        last[i] = pos; 
   }

   // The node will be deleted
   pos = pos->Next[0];
   if (pos != NULL && pos->Data != Data) return false;

   /*Second step: each layer performs deletion*/
   for (int i = S->Level - 1; i >= 0; i--) {
        if (last[i]->Next[i] == pos)
            last[i]->Next[i]  = pos->Next[i];
   } 

   /*Third step：remove the invalid layers 
   * that may be caused by deleting nodes
   */ 
  Skiplist_Node tmp = S->Head; 
  while (S->Level > 1 && tmp->Next[S->Level - 1] == NULL) 
    S->Level--; 
  S->Num--; 
  Skiplist_FreeNode(pos);
  return true;
}

//  Get header elements
int Skiplist_Find_Header(Skiplist S) {
    if (S == NULL || S->Num == 0) return -1;
    Skiplist_Node pos = S->Head;
    return pos->Next[0]->Data;
} 

// Take out the head element
int Skiplist_Delete_Header(Skiplist S) {
    if (S == NULL || S->Num == 0) return -1;

    Skiplist_Node pos = S->Head;
    Skiplist_Node first = pos->Next[0]; // first element

    // delete the head element 
    for (int i = S->Level - 1; i >= 0; i--) {
        if (pos->Next[i] == first)
            pos->Next[i] = first->Next[i];
    } 

    // Erase high invalid levels
    pos = S->Head;
    while (S->Level > 1 && pos->Next[S->Level - 1] == NULL)
        S->Level--;

    int data = first->Data;
    Skiplist_FreeNode(first);
    return data;
}

// Get the number of elements
static int Len(Skiplist S) {
    if (S != NULL) return 0;
    return S->Num;
}

void Skiplist_Print(Skiplist S) {
    if (S == NULL) return;

    Skiplist_Node head = S->Head;
    Skiplist_Node pos;
    for (int i = S->Level - 1; i >= 0; i--) {
        pos = head->Next[i];
        printf("Level[%d]: ", i);
        while (pos != NULL) {
            printf("%d -> ", pos->Data);
            pos = pos->Next[i];
        }
        printf("NULL\n");
    }
}