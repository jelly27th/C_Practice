#ifndef _PAIRINGHEAP_H
#define _PAIRINGHEAP_H
#include <stdlib.h>
#include <stdbool.h>

typedef int PairHeap_ElementType;
typedef struct PairNode {
    PairHeap_ElementType Element;
    struct PairNode* Left;
    struct PairNode* NextSibling;
    struct PairNode* Prev;
}PairNode, *PairHeap;
typedef PairHeap PairHeap_Position;

static PairHeap_Position NullNode = NULL;
PairHeap_Position Location;
static PairHeap_Position CompareAndLink(PairHeap_Position First, PairHeap_Position Second);
PairHeap PairHeap_Init();
PairHeap PairHeap_Insert(PairHeap H, PairHeap_ElementType Item);
static PairHeap Insert(PairHeap H, PairHeap_ElementType Item, PairHeap* Loc);
PairHeap PairHeap_DecreaseKey(PairHeap H, PairHeap_Position Tail, PairHeap_ElementType Dalta);
PairHeap_ElementType PairHeap_FindMin(PairHeap H);
PairHeap PairHeap_DeleteMin(PairHeap_ElementType* MinItem, PairHeap H);
static PairHeap CombineSiblings(PairHeap_Position FirstSibling);
void PairHeap_Print(PairHeap H);
static void PrintHeap(PairHeap H, int depth);
static void PrintDepth(PairHeap_ElementType Item, int depth);

#endif