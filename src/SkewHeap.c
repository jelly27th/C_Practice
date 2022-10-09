/**
 * @file SkewHeap.c
 * @author Jelly (wugd827@163.com)
 * @brief I'm not doing tests for now, maybe not in the future
 * @version 0.1
 * @date 2022-10-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "SkewHeap.h"
#include <stdlib.h>

SkewHeap SkewHeap_Init(SkewHeap_ElementType element)
{
    SkewHeap H = malloc(sizeof(SkewHeapNode));
    H->Left = H->Right = NULL;
    H->element = element;

    return H;
}

SkewHeap SkewHeap_Merge(SkewHeap H1, SkewHeap H2)
{
    if(H1==NULL) return H2;
    if(H2==NULL) return H1;

    if(H1->element>H2->element)
       Swap(H1,H2);
    
    Swap(H1->Left,H2->Right);

    H1->Left = SkewHeap_Merge(H2,H1->Left);

    return H1;
}

static void Swap(SkewHeap H1, SkewHeap H2)
{
    SkewHeap temp = H1;
    H1 = H2;
    H2 = temp;
}
