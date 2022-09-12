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
    percolateUp(H, X);
}

static void percolateUp(BinHeap H, BinHeapElementType X)
{
    if(BinHeapIsFull(H))
    {
        printf("BinHeap if full\n");
        return ;
    }
    
    int i;
    for(i= ++H->Size;H->Elements[i/2]>X;i/=2)
      H->Elements[i] = H->Elements[i/2];
    
    H->Elements[i] = X;
}

bool BinHeapIsEmpty(BinHeap H)
{
    return H->Size == 0;
}

BinHeapElementType BinHeapDeleteMin(BinHeap H)
{
    return percolateDown(H);
}

static BinHeapElementType percolateDown(BinHeap H)
{
    int i, Child;
    BinHeapElementType MinElement ,LastElement;

    if(BinHeapIsEmpty(H))
    {
        printf("BinHeap is empty\n");
        return H->Elements[0];
    }

    MinElement = H->Elements[1];
    LastElement = H->Elements[H->Size--];

    for(i = 1; 2*i <= H->Size; i = Child)
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
    H->Elements[i] = LastElement;
    return MinElement;
}

void BinHeapPrint(BinHeap H)
{
    for(int i = 1; i <= H->Size; i++)
       printf("%d ", H->Elements[i]);
    printf("\n");
}