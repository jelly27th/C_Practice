#include "AAtree.h"
#include <stdio.h>

AAtree AAtree_Init() {
    if (NullNode == NULL) {
        NullNode = malloc(sizeof(AANode));
        NullNode->Left = NullNode->Right = NullNode;
        NullNode->Level = 0;
    }
    return NullNode;
}

// If T's left child is on the same level as T, 
// perform a roation.
static AAtree Skew(AAtree T) {
    if (T->Left->Level == T->Level)
        T = SingleRightRoate(T);
    return T;
} 

// If T's rightmost grandchild is on the same level as T, 
// rotate right child up.
static AAtree Split(AAtree T) {
    if (T->Right->Right->Level == T->Level) {
        T = SingleLeftRoate(T);
        T->Level++;
    }
    return T;
}

/*
*     X --> R --> G                      R
*    /     /      \       ---->         / \ 
*   A     B        C    left roation   X   G         
*                                     / \   \
*                                    A   B   C
*/
static AAtree_Position SingleLeftRoate(AAtree_Position X) {
    AAtree_Position R = X->Right;

    X->Right = R->Left;
    R->Left = X;

    return R;
}

/*
*       X <-- P                         X --> P
*      / \     \       --->            /     / \  
*     A   B     C    right roation    A     B   C
*/
static AAtree_Position SingleRightRoate(AAtree_Position P) {
    AAtree_Position X = P->Left;

    P->Left = X->Right;
    X->Right = P;

    return X;
}

AAtree AAtree_Insert(AAtree T, AATREE_ElementType Item) {
    if (T == NullNode) {
        // Create and a one-node tree
        T = malloc(sizeof(AANode));
        T->Element = Item;
        T->Level = 1;
        T->Left = T->Right = NullNode;
        return T;
    } else {
        if (Item < T->Element)
            T->Left = AAtree_Insert(T->Left, Item);
        else
            T->Right = AAtree_Insert(T->Right, Item);
    }
    // Otherwise it's a duplicate, do nothing
    T = Skew(T);
    T = Split(T);
    return T;
}

AAtree AAtree_Remove(AAtree T, AATREE_ElementType Item) {
    static AAtree_Position DeletePtr, LastPtr;

    if (T != NullNode) {
        // Step 1 : Search down tree set LastPtr and DeletePtr.
        LastPtr = T;
        if (Item < T->Element)
            T->Left = AAtree_Remove(T->Left, Item);
        else {
            DeletePtr = T;
            T->Right = AAtree_Remove(T->Right, Item);
        }
        // Step 2 : If at the bottom of the tree and
        // Item is present, we remove it.
        if (T == LastPtr) {
            if (DeletePtr != NullNode && Item == DeletePtr->Element) {
                DeletePtr->Element = T->Element;
                DeletePtr = NullNode;
                T = T->Right;
                free(LastPtr);
            }
        } else {
            // Step 3 : Otherwise, we are not at the bottom, rebalance.
            if (T->Left->Level < T->Level - 1 || T->Right->Level < T->Level - 1) {
                if (T->Right->Level > (--T->Level))
                    T->Right->Level = T->Level;
                T = Skew(T);
                T->Right = Skew(T->Right);
                T->Right->Right = Skew(T->Right->Right);
                T = Split(T);   
                T->Right = Split(T->Right);
            }
        }

    }
    return T;
}

void AAtree_Print(AAtree T, int Level) {
    if (T != NullNode) {
        AAtree_Print(T->Left, Level);

        int num = Level - T->Level;
        for (int i = 0; i < num; i++)
            printf("    ");
        printf("%d\n", T->Element);

        AAtree_Print(T->Right, Level);
    }
}