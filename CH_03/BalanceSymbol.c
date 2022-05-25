/**
 * @file BalanceSymbol.c
 * @author Jelly (wugd827@163.com)
 * @brief Exercise 3.18
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
ElementType Pop(Stack S);
bool IsFull(Stack S);
bool IsEmpty(Stack S);
int CheckSymbol(const char* path);

int main(int argc, char** argv)
{
    // char path[] =  "G:\\Storage\\Code\\C\\CH_03\\stack.c";
    char path[] =  "E:\\desktop\\Graphics\\test.txt";
    
    CheckSymbol(path);
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
// check the balance symbol
int CheckSymbol(const char* path)
{
    FILE *fp = fopen(path, "r");
    char ch,ch2;
    Stack S = CreatStack(10);
    while ((ch = fgetc(fp)) != EOF)
    {
        //detect open symbols
        if(ch=='('||ch=='{'||ch=='[')
           Push(S,ch);
        else if(ch=='/')
        {
            ch2 = fgetc(fp);
            if(ch2!=EOF&&ch2=='*')
              Push(S,ch);
        }
        // detect close symbols
        switch(ch)
        {
            case ')': if(IsEmpty(S)||Pop(S)!='(')
                      {
                        printf("No find a pair of ()\n");
                        return 0;
                      }
                      break;
            case '}': if(IsEmpty(S)||Pop(S)!='{')
                      {
                        printf("No find a pair of {}\n");
                        return 0;
                      }
                      break;
            case ']': if(IsEmpty(S)||Pop(S)!='[')
                      {
                        printf("No find a pair of []\n");
                        return 0;
                      }
                      break;
            case '*': ch2 = fgetc(fp);
                      if(ch2=='/')
                      {
                        if(IsEmpty(S)||Pop(S)!='/')
                        {
                            printf("No find a pair of //* *//\n");
                            return 0;
                        }
                      }
                      break;
            default: break;
        }
    }
    if(!IsEmpty(S)) 
    {
        printf("the stack is not empty\n");
        return 0;
    }
    fclose(fp);
    return 1;
}