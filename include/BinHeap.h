#ifndef _BINHEAP_H
#define _BINHEAP_H
#include <stdbool.h>

// default data type is int
typedef int BinHeapElementType;
typedef struct _Binheap Binheap;
typedef Binheap * BinHeap;
#define NONUM -1
#define NONE -2

struct _Binheap {
    int Capacity;
    int Size;
    BinHeapElementType *Elements;
};

static int percolateDown(BinHeap H, BinHeapElementType X, int Pos);
static int percolateUp(BinHeap H, BinHeapElementType LastElement,int Pos);
BinHeap BinHeapInit(int MaxSize);
bool BinHeapIsFull(BinHeap H);
bool BinHeapIsEmpty(BinHeap H);
void BinHeapInsert(BinHeap H, BinHeapElementType X);
BinHeapElementType BinHeapDeleteMin(BinHeap H, int Pos);
void BinHeapPrint(BinHeap H);
BinHeapElementType BinHeapFindMin(BinHeap H);
BinHeap BinHeapDestory(BinHeap H);
int BinHeapDecraseKey(BinHeap H, int Offset, int Pos);
void BinHeapIncreaseKey(BinHeap H, int Offset, int Pos);
void BinHeapDelete(BinHeap H, int Pos);
void BinHeapBuildHeap(BinHeap H);


#endif