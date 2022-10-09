#ifndef _LEFTHEAP_H
#define _LEFTHEAP_H
#include <stdbool.h>

typedef int Leftheap_element_type;
typedef struct _LeftHeapNode LeftHeapNode;
typedef LeftHeapNode* Leftheap;
struct _LeftHeapNode{
    Leftheap_element_type element;
    Leftheap Left;
    Leftheap Right;
    int NPL;
};

Leftheap Leftheap_Init(Leftheap_element_type element);
Leftheap_element_type Leftheap_FinMin(Leftheap H);
bool Leftheap_IsEmpty(Leftheap H);
Leftheap Leftheap_Merge(Leftheap H1, Leftheap H2);
#define Leftheap_Insert(X,H) (H = Leftheap_Insert1((X),H))
Leftheap Leftheap_Insert1(Leftheap_element_type X, Leftheap H);
#define Leftheap_DeleteMin(H) (H = Leftheap_DeleteMin1((H)));
Leftheap Leftheap_DeleteMin1(Leftheap H);
static Leftheap Leftheap_Merge1(Leftheap H1, Leftheap H2);
static void SWapChildren(Leftheap H);

#endif