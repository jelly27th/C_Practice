#ifndef _BINOMIAHEAP_H
#define _BINOMIAHEAP_H
#include <stdbool.h>

#define BinomialHeapMax 10
typedef int BinomialHeap_ElementType;
typedef struct _BinomialHeapNode BinomialHeapNode;
typedef BinomialHeapNode* BinomialHeap;
typedef struct BinomialHeap_Collection BinoCollection;
typedef struct BinomialHeap_Collection* BinomialHeapQueue;

struct _BinomialHeapNode{
    BinomialHeap_ElementType element;
    BinomialHeap LeftChild;
    BinomialHeap NextSibling;
};

struct BinomialHeap_Collection{
    int currentSize;//the size of the all nodes
    BinomialHeap TheTrees[BinomialHeapMax];
};

BinomialHeap BinomialHeap_CombineTrees(BinomialHeap T1, BinomialHeap T2);
BinomialHeapQueue BinomialHeapQueue_Init();
BinomialHeapQueue BinomialHeapQueue_Merge(BinomialHeapQueue H1, BinomialHeapQueue H2);
BinomialHeap_ElementType BinomialHeapQueue_DeleteMin(BinomialHeapQueue H);
bool BinomialHeapQueue_IS_Empty(BinomialHeapQueue H);
void BinomialHeapQueue_Insert(BinomialHeapQueue H, BinomialHeap_ElementType Element);

#endif