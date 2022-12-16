#include "PairingHeap.h"
#include <stdio.h>

/*
*             F                S--- C
*            /       +        /
*           A                B 
* If  F <= S
*           _ F <-----> C
*            /|
*           /
*         \/_
*        _S  <-----> A 
*        /|
*       /
*     \/_
*     B
* If  F > S
*           _ S <-----> C
*            /|
*           /
*         \/_
*        _F  <-----> B 
*        /|
*       /
*     \/_
*     A
*/
// This is the basic operation to maintain order.
// Links First and Second together to satisfy heap order.
// Returns the resulting tree.
// First is assumed NOT NullNode.
// First->NextSibling MUST be NullNode on entry.
static PairHeap_Position CompareAndLink(PairHeap_Position First, PairHeap_Position Second) {
    if (Second == NullNode)
        return First;
    else if (First->Element <= Second->Element) {
        // Attack Second as the leftmost childs of First.
        Second->Prev = First;
        First->NextSibling = Second->NextSibling;
        if (First->NextSibling != NullNode)
            First->NextSibling->Prev = First;
        Second->NextSibling = First->Left;
        if (Second->NextSibling != NullNode)
            Second->NextSibling->Prev = Second;
        First->Left = Second;
        return First;
    } else {
        // Attack First as the leftmost child of Second
        Second->Prev = First->Prev;
        First->Prev = Second;
        First->NextSibling = Second->Left;
        if (First->NextSibling != NullNode)
            First->NextSibling->Prev = First;
        Second->Left = First;
        return Second;
    }
}

PairHeap PairHeap_Init() {
    if (NullNode == NullNode) {
        NullNode = malloc(sizeof(PairNode));
        NullNode->Prev = NullNode->Left = 
        NullNode->NextSibling = NullNode;
    }
    return NullNode;
}

PairHeap PairHeap_Insert(PairHeap H, PairHeap_ElementType Item) {
    return Insert(H, Item, &Location);
}

// Insert Item into pairing heap H.
// Return resulting pairing heap.
// A pointer to the newly allocated node is
// passed back by reference and accessed as *Loc.
static PairHeap Insert(PairHeap H, PairHeap_ElementType Item, PairHeap* Loc) {
    PairHeap_Position NewNode;

    NewNode = malloc(sizeof(PairNode));
    NewNode->Element = Item;
    NewNode->Left = NewNode->NextSibling = 
    NewNode->Prev = NullNode;

    *Loc = NewNode;
    if (H == NullNode)
        return NewNode;
    else
        return CompareAndLink(H, NewNode);
}

// Lower item in Position P by Delta.
PairHeap PairHeap_DecreaseKey(PairHeap H, PairHeap_Position Tail, PairHeap_ElementType Dalta) {
    if (Dalta < 0) {
        printf("DecreasKey called with negative Dalta\n");
        return H;
    }

    Tail->Element -= Dalta;
    if (Tail == H)
        return H;
    
    if (Tail->NextSibling != NullNode)
        Tail->NextSibling->Prev = Tail->Prev;
    if (Tail->Prev->Left == Tail)
        Tail->Prev->Left = Tail->NextSibling;
    else
        Tail->Prev->NextSibling = Tail->NextSibling;
    
    Tail->NextSibling = NullNode;
    return CompareAndLink(H, Tail);
}

PairHeap_ElementType PairHeap_FindMin(PairHeap H) {
    return H->Element;
}

static bool IsEmpty(PairHeap H) {
    return H == NullNode;
}

PairHeap PairHeap_DeleteMin(PairHeap_ElementType* MinItem, PairHeap H) {
    PairHeap_Position NewRoot = NullNode;

    if (IsEmpty(H)) {
        printf("Pairing Heap is empty\n");
        return H;
    } else {
        *MinItem = H->Element;
        if (H->Left != NullNode)
            NewRoot = CombineSiblings(H->Left);
        free(H);
    }
    return NewRoot;
}

// Assume FirstSibling is Not NullNode
static PairHeap CombineSiblings(PairHeap_Position FirstSibling) {
    static PairHeap_Position TreeArray[200];
    int i, j, NumSiblings;

    // If only one tree, return it
    if (FirstSibling->NextSibling == NullNode)
        return FirstSibling;
    
    // Place each subtree inn TreeArray
    for (NumSiblings = 0; FirstSibling != NullNode; ++NumSiblings) {
        TreeArray[NumSiblings] = FirstSibling;
        FirstSibling->Prev->NextSibling = NullNode; // Break links
        FirstSibling = FirstSibling->NextSibling;
    }
    TreeArray[NumSiblings] = NullNode;

    // Combine the subtree two at a time,
    // going left to right.
    for (i = 0; i + 1< NumSiblings; i += 2) {
        TreeArray[i] = CompareAndLink(TreeArray[i], TreeArray[i + 1]);
    }

    // j has the result of the last CompareAndLink.
    // If an odd number of trees is found, get the last one.
    j = i - 2;
    if (j == NumSiblings - 3)
        TreeArray[j] = CompareAndLink(TreeArray[j], TreeArray[j + 2]);
    
    // Now go right to left, merging last tree with next to last.
    // The result becomes the new last.
    for ( ; j >= 2; j -=2)
        TreeArray[j - 2] = CompareAndLink(TreeArray[j - 2], TreeArray[j]);
    
    return TreeArray[0];
}

void PairHeap_Print(PairHeap H) {
    PrintHeap(H, 0);
}

static void PrintHeap(PairHeap H, int depth) {
    if (H == NullNode) {
        printf("Wrong heap!\n");
        return ;
    }

    if (H->Left != NullNode)
        PrintHeap(H->Left, depth + 1);

    PrintDepth(H->Element, depth + 1); 

    if (H->NextSibling != NullNode)
        PrintHeap(H->NextSibling, depth + 1);
}

static void PrintDepth(PairHeap_ElementType Item, int depth) {
    while (depth != 0) {
        printf("   ");
        depth--; 
    }
    printf("%d\n", Item);
}