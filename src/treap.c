#include "treap.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/*
*     X --> R --> G                      R
*    /     /      \       ---->         / \ 
*   A     B        C    left roation   X   G         
*                                     / \   \
*                                    A   B   C
*/
static Treap_Position SingleLeftRoate(Treap_Position X) {
    Treap_Position R = X->Right;

    X->Right = R->Left;
    R->Left = X;

    return R;
}

/*
*       X <-- P                         X --> P
*      / \     \       --->            /     / \  
*     A   B     C    right roation    A     B   C
*/
static Treap_Position SingleRightRoate(Treap_Position P) {
    Treap_Position X = P->Left;

    P->Left = X->Right;
    X->Right = P;

    return X;
}

Treap Treap_Init() {
    if (NullNode == NULL) {
        NullNode = malloc(sizeof(TreapNode));
        NullNode->Left = NullNode->Right = NullNode;
        NullNode->Priority = Infinity;
    }
    // Reset time, set seed
    srand(time(0));
    return NullNode;
}

Treap Treap_Insert(Treap T, Treap_ElementType Item) {
    if (T == NullNode) {
        // Create and return a one-node tree
        T = malloc(sizeof(TreapNode));
        T->Element = Item;
        T->Priority = rand() % Infinity; // Generate random 0 ~ Infinity - 1
        T->Left = T->Right = NullNode;
    } else if (Item < T->Element){
        T->Left = Treap_Insert(T->Left, Item);
        if (T->Left->Priority < T->Priority)
            T = SingleRightRoate(T);
    } else if (Item > T->Element) {
        T->Right = Treap_Insert(T->Right, Item);
        if (T->Right->Priority < T->Priority)
            T = SingleLeftRoate(T);
    }
    // Otherwise it's a duplicate, do nothing
    return T;
}

Treap Treap_Remove(Treap T, Treap_ElementType Item) {
    if (T != NullNode) {
        if (Item < T->Element)
            T->Left = Treap_Remove(T->Left, Item);
        else if (Item > T->Element) 
            T->Right = Treap_Remove(T->Right, Item);
        else {
            // Match found
            if (T->Left->Priority < T->Right->Priority)
                T = SingleRightRoate(T);
            else 
                T = SingleLeftRoate(T);

            if (T != NullNode) // Continue on down
                T = Treap_Remove(T, Item);
            else {
                // At a leaf
                free(T->Left);
                T->Left = NullNode;
            }
        }
    }
    return T;
}

void Treap_Print(Treap T, int depth) {
    if (T != NullNode) {
        Treap_Print(T->Left, depth + 1);

        for (int i = 0; i < depth; i++) {
            printf("        ");
        }
        printf("%d, %d\n", T->Element, T->Priority);

        Treap_Print(T->Right, depth + 1);
    }
}