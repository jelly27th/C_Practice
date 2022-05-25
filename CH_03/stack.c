/**
 * @file stack.c
 * @author 吴国栋 (872908391@qq.com)
 * @brief 实现栈(数组)
 * @version 0.1
 * @date 2022-05-24
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define EmptyTOS -1
typedef int ElementType;
typedef struct StackRecord* Stack;
struct StackRecord {
    int Capacity;
    int TopOfStack;
    ElementType *Array;
};

Stack CreatStack(int MaxStackSize);
void MakeEmpty(Stack S);
void clearStack(Stack S);
ElementType Push(Stack S,ElementType element);
void Pop(Stack S);
bool IsFull(Stack S);

int main(int argc, char** argv)
{
    Stack S = CreatStack(5);
    Push(S,5);
    Push(S,4);
    Push(S,3);
    Push(S,2);
    Push(S,1);
    for(int i = 0; i <5;i++)
    {
        printf("%d ",S->Array[i]);
    }
    return 0;
}
// create a stack
Stack CreatStack(int MaxStackSize)
{
    Stack S = malloc(sizeof(struct StackRecord));
    S->Array = malloc(sizeof(ElementType)*MaxStackSize);
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
ElementType Push(Stack S,ElementType element)
{
    if(IsFull(S))
        printf("the stack is full\n");
    else 
        S->Array[++S->TopOfStack] = element;
    return 0;
}
// pop Stack
void Pop(Stack S)
{
    S->TopOfStack--;
}

bool IsFull(Stack S)
{
    if(S->Capacity==(S->TopOfStack+1)) return true;
    else  return false;
}