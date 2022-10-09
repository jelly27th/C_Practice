/**
 * @file LeftHeap.c
 * @author Jelly (wugd827@163.com)
 * @brief I'm not doing tests for now, maybe not in the future
 * @version 0.1
 * @date 2022-10-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <Leftheap.h>
#include <stdlib.h>
#include <stdio.h>

static void SWapChildren(Leftheap H)
{
    Leftheap temp = H->Left;
    H->Left = H->Right;
    H->Right = temp;
}

Leftheap Leftheap_Init(Leftheap_element_type element)
{
    Leftheap H = malloc(sizeof(LeftHeapNode));
    H->Left = NULL;
    H->Right = NULL;
    H->NPL = 0;
    H->element = element;

    return H;
}
// the root of left heap is minimum value 
Leftheap_element_type Leftheap_FinMin(Leftheap H)
{
    return H->element;
}

bool Leftheap_IsEmpty(Leftheap H)
{
    return H==NULL;
}

Leftheap Leftheap_Merge(Leftheap H1, Leftheap H2)
{
    if(H1==NULL) return H2;
    if(H2==NULL) return H1;
    if(H1->element<H2->element)
      return Leftheap_Merge1(H1,H2);
    else 
      return Leftheap_Merge1(H2,H1);
}

static Leftheap Leftheap_Merge1(Leftheap H1, Leftheap H2)
{
    if(H1->Left == NULL)
      H1->Left = H2;
    else
    {
        H1->Right = Leftheap_Merge(H1->Right,H2);
        if(H1->Left->NPL<H1->Right->NPL)
          SWapChildren(H1);
        
        H1->NPL = H1->Right->NPL + 1;
    }
    return H1;
}

Leftheap Leftheap_Insert1(Leftheap_element_type X, Leftheap H)
{
    Leftheap SingelNode =  Leftheap_Init(X);
    H = Leftheap_Merge(SingelNode, H);
    return H;
}

Leftheap Leftheap_DeleteMin1(Leftheap H)
{
    Leftheap Left, Right;
    if(Leftheap_IsEmpty(H))
    {
        printf("Leftheap is empty\n");
        return H;
    }

    Left = H->Left;
    Right = H->Right;
    free(H);
    return Leftheap_Merge(Left, Right);
}

