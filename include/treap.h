#ifndef _TREAP_H
#define _TREAP_H
#include <stdlib.h>

#define Infinity (0x7fffffff)
typedef int Treap_ElementType;
typedef struct TreapNode {
    Treap_ElementType Element;
    struct TreapNode* Left;
    struct TreapNode* Right;
    int Priority;
}TreapNode, *Treap;

typedef Treap Treap_Position;
static Treap_Position NullNode = NULL;
static Treap_Position SingleLeftRoate(Treap_Position X);
static Treap_Position SingleRightRoate(Treap_Position P);
Treap Treap_Init();
Treap Treap_Insert(Treap T, Treap_ElementType Item);
Treap Treap_Remove(Treap T, Treap_ElementType Item);
void Treap_Print(Treap T, int depth);

#endif