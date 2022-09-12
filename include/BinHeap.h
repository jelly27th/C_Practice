#ifndef _BINHEAP_H
#define _BINHEAP_H
#include <stdbool.h>

typedef int BinHeapElementType;
typedef struct _Binheap Binheap;
typedef Binheap * BinHeap;
#define NONUM -1

struct _Binheap {
    int Capacity;
    int Size;
    BinHeapElementType *Elements;
};

BinHeap BinHeapInit(int MaxSize);
bool BinHeapIsFull(BinHeap H);
bool BinHeapIsEmpty(BinHeap H);
void BinHeapInsert(BinHeap H, BinHeapElementType X);
static void percolateUp(BinHeap H, BinHeapElementType X);
BinHeapElementType BinHeapDeleteMin(BinHeap H);
static BinHeapElementType percolateDown(BinHeap H);
#endif