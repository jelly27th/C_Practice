#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "Stack.h"

// create a stack
Stack CreatStack(int MaxStackSize)
{
    Stack S = malloc(sizeof(struct StackRecord));
    S->Array = malloc(sizeof(StackElementType)*MaxStackSize);
    S->Capacity = MaxStackSize;
    MakeEmpty(S);
    return S;
}
//create a empty stack 
void MakeEmpty(Stack S)
{
    S->TopOfStack = EmptyTOS;
}
// clear stack
void clearStack(Stack S)
{
    if(S!= NULL)
    {
        free(S->Array);
        free(S);
    }
}
// push Stack
void Push(Stack S,StackElementType element)
{
    if(IsFull(S))
        printf("the stack is full\n");
    else 
        S->Array[++S->TopOfStack] = element;
}
// pop the top of element
void Pop(Stack S)
{
    if(!IsEmpty(S))
       S->Array[S->TopOfStack--];
    else
       printf("the stack is empty\n");
}
// check if stack is full
bool IsFull(Stack S)
{
    if(S->Capacity==(S->TopOfStack+1)) return true;
    else  return false;
}
//check if stack is empty
bool IsEmpty(Stack S)
{
    if(S->TopOfStack==-1) return true;
    else return false;
}
// pop the top element of the stack
StackElementType Top(Stack S)
{
    if(IsEmpty(S))
       printf("the stack is empty\n");
    else
      return S->Array[S->TopOfStack];
    return 0;
}
// pop the top element and return the top element
StackElementType TopAndPop(Stack S)
{
    if(IsEmpty(S))
      printf("the stack is empty\n");
    else 
      return S->Array[S->TopOfStack--];
    return 0;
}