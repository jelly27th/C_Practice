#ifndef _123_SKIPLIST_H
#define _123_SKIPLIST_H
#include <stdlib.h>
#include <stdbool.h>

typedef int SkipList_123_ElementType;
typedef struct SkipListNode_123 {
    SkipList_123_ElementType Element;
    struct SkipListNode_123* Right;
    struct SkipListNode_123* Down;
}SkipListNode_123, *SkipList_123;

typedef SkipList_123 SkipList_123_Postion;
static SkipList_123_Postion Bottom = NULL;
static SkipList_123_Postion Tail = NULL;

#define Infinity (999)
SkipList_123 SkipList_123_Init();
SkipList_123_Postion SkipList_123_Find(SkipList_123 L, SkipList_123_ElementType Item);
SkipList_123 SkipList_123_Insert(SkipList_123 L, SkipList_123_ElementType Item);
void SkipList_123_Print(SkipList_123 L);
SkipList_123 SkipList_123_Remove(SkipList_123 L, SkipList_123_ElementType Item);
static bool IsEmpty(SkipList_123 L);
static SkipList_123 LowerHeadRemoveHelp(SkipList_123 L);
static SkipList_123 FindAndModifyRemoveHelp(SkipList_123 L, SkipList_123_ElementType Cur_Value, SkipList_123_ElementType Pre_Value);

#endif