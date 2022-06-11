/**
 * @file TwoStacks.c
 * @author Jelly (wugd827@163.com)
 * @brief Exercise 3.21
 * @version 0.1
 * @date 2022-05-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define EmptyTOS -1
#define STACK_SIZE 10
typedef int ElementType;
typedef struct StackRecord* Stack;
struct StackRecord {
    int Capacity;
    int BottomOfStack;
    int TopOfStack;
    ElementType *Array;
};
Stack CreatStack(int MaxStackSize);
ElementType PushBottom(Stack S,ElementType element);
ElementType PushTop(Stack S,ElementType element);
ElementType PopBottom(Stack S);
ElementType PopTop(Stack S);
bool IsFull(Stack S);
bool IsTopEmpty(Stack S);
bool IsButtomEmpty(Stack S);
void clearStack(Stack S);
ElementType TopTop(Stack S);
ElementType BottomTop(Stack S);
void MakeEmpty(Stack S);

int main(int argc, char** argv)
{
    Stack S = CreatStack(10);
    PushBottom(S,0);
    PushBottom(S,1);
    PushBottom(S,2);
    PushBottom(S,3);
    PushBottom(S,4);
    PushTop(S,10);
    PushTop(S,9);
    PushTop(S,8);
    PushTop(S,7);
    printf("%d %d\n",TopTop(S),BottomTop(S));
    clearStack(S);
    return 0;
}

// use a array to create two stacks
Stack CreatStack(int MaxStackSize)
{
    Stack S = malloc(sizeof(struct StackRecord)*MaxStackSize);
    S->Array = malloc(sizeof(ElementType)*MaxStackSize);
    S->Capacity = MaxStackSize;
    MakeEmpty(S);
    return S;
}
//Push bottom of stack
ElementType PushBottom(Stack S,ElementType element)
{
    if(IsFull(S))
      printf("two stack is full\n");
    else
      S->Array[++S->BottomOfStack] = element;
    return 0;
      
}
//Push top of stack
ElementType PushTop(Stack S,ElementType element)
{
    if(IsFull(S))
      printf("two stack is full\n");
    else
      S->Array[--S->TopOfStack] = element;
    return 0; 
}
// pop bottom of stack
ElementType PopBottom(Stack S)
{
    if(IsButtomEmpty(S))
       printf("the buttom of stack is empty\n");
    else
       return S->Array[S->BottomOfStack--];
    return 0;
}
// pop top of stack
ElementType PopTop(Stack S)
{
    if(IsTopEmpty(S))
       printf("the top of stack is empty\n");
    else
       return S->Array[S->TopOfStack++];
    return 0; 
}
// check if stack is full
bool IsFull(Stack S)
{
    if(S->BottomOfStack==S->TopOfStack) return true;
    else return false;
}
// check if the top of stack is empty
bool IsTopEmpty(Stack S)
{
    if(S->TopOfStack==S->Capacity) return true;
    else return false;
}
// check if the buttom of stack is empty
bool IsButtomEmpty(Stack S)
{
    if(S->BottomOfStack==EmptyTOS) return true;
    else return false;
}
// clear the top of stack and the bottom of stack
void clearStack(Stack S)
{
    if(S!= NULL)
    {
        free(S->Array);
        free(S);
    }
}
// pop the top element of the top of stack
ElementType TopTop(Stack S)
{
    return S->Array[S->TopOfStack];
}
// pop the top of stack of the buttom of stack 
ElementType BottomTop(Stack S)
{
    return S->Array[S->BottomOfStack];
}
// create a empty stack
void MakeEmpty(Stack S)
{
    S->BottomOfStack = EmptyTOS;//bottom of stack -1
    S->TopOfStack = S->Capacity;//top of stack + 1
}