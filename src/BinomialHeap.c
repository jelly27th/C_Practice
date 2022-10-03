/**
 * @file BinomialHeap.c
 * @author Jelly (wugd827@163.com)
 * @brief I'm not doing tests for now, maybe not in the future
 * @version 0.1
 * @date 2022-10-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdlib.h>
#include <stdio.h>
#include "BinomialHeap.h"

BinomialHeap 
BinomialHeap_CombineTrees(BinomialHeap T1, BinomialHeap T2)
{
    if(T1->element>T2->element)
      return CombineTrees(T2,T1);
    T2->NextSibling = T1->LeftChild;
    T1->LeftChild = T2;
    return T1;
}

BinomialHeapQueue BinomialHeapQueue_Init()
{
    BinomialHeapQueue T = malloc(sizeof(BinoCollection));
    T->currentSize = 0;

    for(int i = 0; i < BinomialHeapMax; i++)
      T->TheTrees[i] = NULL;
    return T;
}

BinomialHeapQueue 
BinomialHeapQueue_Merge(BinomialHeapQueue H1, BinomialHeapQueue H2)
{
    BinomialHeap T1, T2, Carry = NULL;

    // if H1 and H2 are same, exit
    if(H1!= NULL&&H2!= NULL&&H1==H2) return H1;
    // if H2 is null, exit
    else if(H1!=NULL&&H2==NULL) return H1;
    
    if(H1->currentSize+H2->currentSize >Bino_Sum())
    {
        printf("Merge will be full.\n");
        return NULL;
    }  

    for(int i=0, j=1;j<=H1->currentSize;i++,j*=2)
    {
        T1 = H1->TheTrees[i];
        T2 = H2->TheTrees[i];

        switch(!!T1+2*!!T2+4*!!Carry)
        {
            case 0: /*no trees*/
            case 1: /*only H1 tree*/
                break;
            case 2: /*only H2 tree*/
               H1->TheTrees[i] = T2;
               H2->TheTrees[i] = NULL;
               break;
            case 4: /*only Carry*/
               H1->TheTrees[i] = Carry;
               Carry = NULL;
               break;
            case 3: /*H1 and H2*/
               Carry = BinomialHeap_CombineTrees(T1,T2);
               H1->TheTrees[i] = H2->TheTrees[i] = NULL;
               break;
            case 5: /*H1 and Carry*/
               Carry = BinomialHeap_CombineTrees(T1,Carry);
               H1->TheTrees[i] = NULL;
               break;
            case 6: /*H2 and Carry*/
               Carry = BinomialHeap_CombineTrees(T2,Carry);
               H2->TheTrees[i] = NULL;
               break;
            case 7: /*all trees*/
              H1->TheTrees[i] = Carry;
              Carry = BinomialHeap_CombineTrees(T1,T2);
              H2->TheTrees[i] = NULL;
              break;
        }
    }
    return H1;
}

BinomialHeap_ElementType 
BinomialHeapQueue_DeleteMin(BinomialHeapQueue H)
{
    int MinTree;
    BinomialHeapQueue DeleteQueue;
    BinomialHeap DeleteTree, OldRoot;
    BinomialHeap_ElementType MinItem;

    if(BinomialHeapQueue_IS_Empty(H))
    {
        printf("BinomialHeapQueue is empty\n");
        return -1;
    }

    MinItem = 999;//assume the minimum is big
    for(int i = 0; i < BinomialHeapMax; i++)
    {
        // update the minimum
        if(H->TheTrees[i]&&H->TheTrees[i]->element<MinItem)
        {
            MinItem = H->TheTrees[i]->element;
            MinTree = i;
        }
    }

    // delete the minimum and free memory
    DeleteTree = H->TheTrees[MinTree];
    OldRoot = DeleteTree;
    DeleteTree = DeleteTree->LeftChild;
    free(OldRoot);

    // Generate a new binomial queue
    DeleteQueue = BinomialHeapQueue_Init();
    DeleteQueue->currentSize = (1<<MinTree)-1;
    for(int j = MinTree-1; j>=0; j--)
    {
        DeleteQueue->TheTrees[j] = DeleteTree;
        DeleteTree = DeleteTree->NextSibling;
        DeleteQueue->TheTrees[j]->NextSibling = NULL;
    }

    H->TheTrees[MinTree] = NULL;
    H->currentSize -= DeleteQueue->currentSize+1;

    BinomialHeapQueue_Merge(H,DeleteQueue);
    return MinItem;
}
bool BinomialHeapQueue_IS_Empty(BinomialHeapQueue H)
{
    return H->currentSize==0;
}

void BinomialHeapQueue_Insert(BinomialHeapQueue H, BinomialHeap_ElementType Element)
{
    BinomialHeapQueue single = BinomialHeapQueue_Init();
    single->TheTrees[0] = malloc(sizeof(BinomialHeapNode));
    single->TheTrees[0]->element = Element;
    single->TheTrees[0]->LeftChild = single->TheTrees[0]->NextSibling = NULL;
    single->currentSize = 1;
    BinomialHeapQueue_Merge(H, single);
}

static int Bino_Sum()
{
    int sum = 1;
    int num = 2;
    for(int i = 0; i < BinomialHeapMax; i++)
    {
        num *= 2;
        sum += num;
    }
    return sum;
}