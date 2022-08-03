#include "List.h"
#include <stdlib.h>

int ListIsEmpty(List L)
{
    return L->Next == NULL;
}

int ListIsLast(Postion P, List L)
{
    return P->Next == NULL;
}

Postion ListFind(ListElementType Element, List L)
{
    Postion P;

    P = P->Next;
    while(P!= NULL&&P->Element!=Element)
       P = P->Next;
    
    return P;
}

void ListDelete(ListElementType Element, List L)
{
    Postion P,TmpCell;

    P = ListFindPrevious(Element,L);
    if(!ListIsLast(P, L))
    {
        TmpCell = P->Next;
        P->Next = TmpCell->Next;
        free(TmpCell);
    }
}

Postion ListFindPrevious(ListElementType Element, List L)
{
    Postion P;

    P = L;
    while(P->Next != NULL &&P->Next->Element != Element)
        P = P->Next;
    
    return P;
}

void ListInsert(ListElementType Element, List L, Postion P)
{
    Postion TmpCell;

    TmpCell = malloc(sizeof(ListNode));
    // if(TmpCell == NULL)
    //   FatalError("Out of space!!!");

    TmpCell->Element = Element;
    TmpCell->Next = P->Next;
    P->Next = TmpCell;
}

void DeleteList(List L)
{
    Postion P,Tmp;

    P = L->Next;
    L->Next =  NULL;
    while(P!= NULL)
    {
        Tmp = P->Next;
        free(P);
        P = Tmp;
    }
}