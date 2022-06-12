#ifndef _STACK_H
#define _STACK_H

#include <stdbool.h>
#include "AvlTree.h"
#define EmptyTOS -1
typedef AvlTree StackElementType;
typedef struct StackRecord* Stack;
struct StackRecord {
    int Capacity;
    int TopOfStack;
    StackElementType *Array;
};

bool IsFull(Stack S);
bool IsEmpty(Stack S);
Stack CreatStack(int MaxStackSize);
void clearStack(Stack S);
void MakeEmpty(Stack S);
void Push(Stack S,StackElementType element);
void Pop(Stack S);
StackElementType Top(Stack S);
StackElementType TopAndPop(Stack S);

#endif