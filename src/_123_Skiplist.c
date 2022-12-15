/**
 * @file _123_Skiplist.c
 * @author Jelly (wugd827@163.com)
 * @brief reference to [1-2-3 skip list 确定性跳跃表的实现](https://www.cnblogs.com/rocketfan/archive/2009/08/30/1556797.html)
 * @version 0.1
 * @date 2022-12-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "_123_Skiplist.h"
#include <stdio.h>

SkipList_123 SkipList_123_Init() {
    SkipList_123 L;

    if (Bottom == NULL) {
        Bottom = malloc(sizeof(SkipListNode_123));
        Bottom->Right = Bottom->Down = Bottom;
    }

    Tail = malloc(sizeof(SkipListNode_123));
    Tail->Element = Infinity;
    Tail->Right = Tail;

    // Create the haeder node
    L = malloc(sizeof(SkipListNode_123));
    L->Element = Infinity;
    L->Right = Tail;
    L->Down = Bottom;

    return L;
}

// Return SkipList_123_Postion of node containg Item,
// or Bottom if not found.
SkipList_123_Postion SkipList_123_Find(SkipList_123 L, SkipList_123_ElementType Item) {
    SkipList_123_Postion Current = L;

    Bottom->Element = Item;
    while (Item != Current->Element) {
        if (Item < Current->Element)
            Current = Current->Down;
        else
            Current = Current->Right;
    }
    return Current;
}

SkipList_123 SkipList_123_Insert(SkipList_123 L, SkipList_123_ElementType Item) {
    SkipList_123_Postion Current = L;
    SkipList_123_Postion NewNode;

    Bottom->Element = Item;
    while (Current != Bottom) {
        while (Item > Current->Element)
            Current = Current->Right;
        
        // If gap size is 3 or at bottom level,
        // and must insert, then promote the middle element.
        if ((Current->Element) > (Current->Down->Right->Right->Element)) {
            NewNode = malloc(sizeof(SkipListNode_123));
            NewNode->Right = Current->Right;
            NewNode->Down = Current->Down->Right->Right;
            Current->Right = NewNode;
            NewNode->Element = Current->Element;
            Current->Element = Current->Down->Right->Element;
        }
        Current = Current->Down; 

        // Raise height of DSL if necessary
        if (L->Right != Tail) {
            NewNode = malloc(sizeof(SkipListNode_123));
            NewNode->Down = L;
            NewNode->Right = Tail;
            NewNode->Element = Infinity;
            L = NewNode;
        } 

    }

    return L;
}

void SkipList_123_Print(SkipList_123 L) {
    SkipList_123_Postion Current = L;
    SkipList_123_Postion tmp;
    while (Current->Down != Bottom) {
        tmp = Current->Down;
        do {
            printf("%d ", tmp->Element);
            tmp = tmp->Right;
        } while (tmp != Tail);
        printf("\n");
        Current = Current->Down;
    }
}

SkipList_123 SkipList_123_Remove(SkipList_123 L, SkipList_123_ElementType Item) {
    // If 1-2-3 Skip List can not remove
    if (IsEmpty(L)) 
        return NULL;
    
    // The current node, the previous node of the current node, 
    // start marks the start of each level when the node goes down.
    // If previous finally equal to start means have not advanced toward right on this level.
    // next save the start position of the next level for current node.
    SkipList_123_Postion Current, Previous, Next, tmp;

    Current = L->Down;
    int NodeHeight = 0;
    while (1) { //loop and will return when curent->down == bottom
        Previous = NULL;
        while (Item > Current->Element) { //try advance toward right as far as possible
            Previous = Current;
            Current = Current->Right;
        }  
        //NodeHeight will mark if a node is a height 1 node
        if (Current->Element == Item)
            NodeHeight++;
        
        //if on level 1 try to remove if possible and return
        if (Current->Down == Bottom) {
            if (NodeHeight == 0) {
                L = LowerHeadRemoveHelp(L); //can not find do not  need to remove
                return NULL;
            } else { // Need to remove
                if (NodeHeight == 1) { //if node height == 1 just remove it.
                    //delete need to consider down fild of the upper level.
                    //so swap current and current->right.
                    tmp = Current->Right; // to be deleted
                    Current->Element = Current->Right->Element;
                    Current->Right = tmp->Right;
                    free(tmp);
                    L = LowerHeadRemoveHelp(L); // Might need to lower the head
                } else {
                    //if current node height > 1, swap the key with neighbour than delete the neighbour
                    //here swap with left neigbour,notice we must have advaced right on
                    //this level otherwise it must be a height 1 node.
                    //we will find all the node with key value current->key and modify it
                    //to previous->key.
                    L = LowerHeadRemoveHelp(L); // need to make sure the sturcture correct first.
                    L = FindAndModifyRemoveHelp(L, Current->Element, Previous->Element); 
                    Previous->Right = Current->Right;
                    free(Current);
                }
                return L;
            }
        }

        //on other levels ,not level 1.
        //save the postion to go down on the lower level.
        Next = Current->Down; //the next level will be unchaged when dealing the current level.

        //Note: current->key == current->down->right->key 
        // means the gap we want to down is of size only 1.
        if (Current->Element == Current->Down->Right->Element) {
            //the first gap case, consider current gap and the next
            if (Previous == NULL) { //have not advanced on this level
               //if the next gap has 2 or more one level lower element.
               //one element need to lower down,the other one need to raise one level,
               //just swap do not need to delte space.
               if (Current->Right->Element > Current->Right->Down->Right->Element) {
                    Current->Element = Current->Right->Down->Element;
                    Current->Right->Down = Current->Right->Down->Right;
               } else {
                    //one element need to lower down,need to delete space.
                    tmp = Current->Right;
                    Current->Element = tmp->Element;
                    Current->Right = tmp->Right;
                    free(tmp);
               }
            } else { //not the first so consider the privious gap and the current
                if (Previous->Element > Previous->Down->Right->Element) {
                    tmp = Previous->Down->Right;
                    if (tmp->Right->Element != Previous->Element)
                        tmp = tmp->Right;
                    Previous->Element = tmp->Element;
                    Current->Down = tmp->Right;
                } else {
                    Previous->Element = Current->Element;
                    Previous->Right = Current->Right;
                    free(Current);
                }
            }
        }
        Current = Next; //go to the next level (one level lower).
    }
}

static bool IsEmpty(SkipList_123 L) {
    if (L->Down == Bottom) 
        return true;
    return false;
}

static SkipList_123 LowerHeadRemoveHelp(SkipList_123 L) {
    SkipList_123_Postion tmp;
    if (L->Down->Right == Tail) {
        tmp = L->Down;
        L->Down = tmp->Down;
        free(tmp);
    }
    return L;
}

static SkipList_123 FindAndModifyRemoveHelp(SkipList_123 L, SkipList_123_ElementType Cur_Value, SkipList_123_ElementType Pre_Value) {
    SkipList_123_Postion Current;

    Current = L;
    while (Current != Bottom) {
        while (Cur_Value > Current->Element)
            Current = Current->Right;
        if (Cur_Value == Current->Element)
            Current->Element = Pre_Value;
        Current = Current->Down;
    }
    return L;
}