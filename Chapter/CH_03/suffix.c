/**
 * @file suffix.c
 * @author Jelly (wugd827@163.com)
 * @brief Exercise 3.19
 * @version 0.1
 * @date 2022-05-25
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define EmptyTOS -1
typedef double ElementType;
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
ElementType Pop(Stack S);
bool IsFull(Stack S);
bool IsEmpty(Stack S);
ElementType Suffix(const char * expressions,int length, int Stacksize);

int main(int argc, char** argv)
{
    char expressions[] = "6523+8*+3+/";
    int length = sizeof(expressions) / sizeof(expressions[0]);
    printf("%.f\n",Suffix(expressions, length, 10));
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
// pop Stack and return top of stack Element
ElementType Pop(Stack S)
{
    if(!IsEmpty(S))
       return S->Array[S->TopOfStack--];
    else
       printf("the stack is empty\n");
    return 0;
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
//Evaluate postfix expressions(only consider 0 ~ 9)
ElementType Suffix(const char * expressions,int length, int Stacksize)
{
    Stack S = CreatStack(Stacksize);
    ElementType num = 0;
    for(int i=0;i<length-1; i++)
    {
        if(expressions[i]>='0'&&expressions[i]<='9')
           Push(S,expressions[i]-'0');
        else if(expressions[i]=='+')
        {
            num = Pop(S);
            num +=Pop(S);
            Push(S,num);
        }
        else if(expressions[i]=='-')
        {
            num = Pop(S);
            num -=Pop(S);
            Push(S,num);
        }
        else if(expressions[i]=='*')
        {
            num = Pop(S);
            num *=Pop(S);
            Push(S,num);
        }
        else if(expressions[i]=='/')
        {
            num = Pop(S);
            num /=Pop(S);
            Push(S,num);
        }
    }
    num = Pop(S);
    return num;
}