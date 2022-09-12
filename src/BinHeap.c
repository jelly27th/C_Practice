#include "BinHeap.h"
#include <stdio.h>
#include <stdlib.h>
BinHeap BinHeapInit(int MaxSize)
{
    BinHeap H = malloc(sizeof(Binheap));
    H->Elements = malloc(sizeof(BinHeapElementType) * (MaxSize+1));

    H->Capacity = MaxSize;
    H->Size = 0;
    H->Elements[0] = NONUM;

    return H;
}

bool BinHeapIsFull(BinHeap H)
{
    return H->Size == H->Capacity;
}

void BinHeapInsert(BinHeap H, BinHeapElementType X)
{
    if(BinHeapIsFull(H))
    {
        printf("BinHeap if full\n");
        return ;
    }
    H->Size++;
    int pos = percolateUp(H, X, H->Size); 
    H->Elements[pos] = X;
}

static int percolateUp(BinHeap H, BinHeapElementType X, int Pos)
{   
    int i;
    for(i= Pos;H->Elements[i/2]>X;i/=2)
      H->Elements[i] = H->Elements[i/2];
    
    return i;
}

bool BinHeapIsEmpty(BinHeap H)
{
    return H->Size == 0;
}

BinHeapElementType BinHeapDeleteMin(BinHeap H, int Pos)
{
    if(BinHeapIsEmpty(H))
    {
        printf("BinHeap is empty\n");
        return H->Elements[0];
    }

    BinHeapElementType MinElement = H->Elements[Pos];
    BinHeapElementType LastElement = H->Elements[H->Size--];

    int i = percolateDown(H,LastElement, Pos);
    H->Elements[i] = LastElement;

    return MinElement;
}

static int percolateDown(BinHeap H, BinHeapElementType LastElement, int Pos)
{
    int i, Child;

    for(i = Pos; 2*i <= H->Size; i = Child)
    {
        Child = 2*i;
        if(Child != H->Size && H->Elements[Child + 1] 
                                < H->Elements[Child])
           Child++;
        
        if(LastElement > H->Elements[Child])
           H->Elements[i] = H->Elements[Child];
        else
           break;
    }
    return i;
}

void BinHeapPrint(BinHeap H)
{
    for(int i = 1; i <= H->Size; i++)
       printf("%d ", H->Elements[i]);
    printf("\n");
}

BinHeapElementType BinHeapFindMin(BinHeap H)
{
    if(BinHeapIsEmpty)
    {
        printf("Heap is empty\n");
        return H->Elements[0];
    }
    return H->Elements[1];
}

BinHeap BinHeapDestory(BinHeap H)
{
    free(H->Elements);
    free(H);
    return NULL;
}

int BinHeapDecraseKey(BinHeap H, int Offset, int Pos)
{
    int i;
    if(Offset == NONE || Offset >= H->Elements[Pos])
       return Pos;
    else
    {
        H->Elements[Pos] -= Offset; 
        BinHeapElementType LastElement = H->Elements[Pos];

        i = percolateUp(H,LastElement,Pos);
        if(i != Pos) H->Elements[i] = LastElement;
    }
    return i;
}

void BinHeapIncreaseKey(BinHeap H, int Offset, int Pos)
{
    H->Elements[Pos] += Offset;
    BinHeapElementType LastElement = H->Elements[Pos];

    int i = percolateDown(H, LastElement, Pos);
    if(i != Pos) H->Elements[i] = LastElement;
}

void BinHeapDelete(BinHeap H, int Pos)
{
    int pos = BinHeapDecraseKey(H, NONE,Pos);
    BinHeapDeleteMin(H, Pos);
}

void BinHeapBuildHeap(BinHeap H)
{
    int N = H->Size, pos = 0;
    BinHeapElementType LastElement;
    for(int i = N/2; i > 0; i--)
    {
        LastElement = H->Elements[i];
        pos = percolateDown(H,LastElement, i);
        if(pos != i) H->Elements[pos] = LastElement;
    }
}