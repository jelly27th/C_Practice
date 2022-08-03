#ifndef _LIST_H
#define _LIST_H

typedef int ListElementType;
typedef struct _ListNode ListNode;
typedef ListNode* List;
typedef ListNode* Postion;
typedef List* ListAdress;

struct _ListNode{
    ListElementType Element;
    Postion Next;
};

int ListIsEmpty(List L);
int ListIsLast(Postion P, List L);
Postion ListFind(ListElementType Element, List L);
void ListDelete(ListElementType Element, List L);
Postion ListFindPrevious(ListElementType Element, List L);
void ListInsert(ListElementType Element, List L, Postion P);
void DeleteList(List L);

#endif