#ifndef _SKEWHEAP_H
#define _SKEWHEAP_H

typedef int SkewHeap_ElementType;
typedef struct _SkewHeapNode SkewHeapNode;
typedef SkewHeapNode* SkewHeap;

struct _SkewHeapNode{
    SkewHeap_ElementType element;
    SkewHeap Right;
    SkewHeap Left;
};

SkewHeap SkewHeap_Init(SkewHeap_ElementType element);
SkewHeap SkewHeap_Merge(SkewHeap H1, SkewHeap H2);
static void Swap(SkewHeap H1, SkewHeap H2);

#endif