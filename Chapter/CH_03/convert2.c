/**
 * @file convert2.c
 * @author Jelly (wugd827@163.com)
 * @brief Exercise 3.20(c)
 * @version 0.1
 * @date 2022-05-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EmptyTOS -1
#define STACK_SIZE 10
typedef char* ElementType;
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
ElementType Top(Stack S);
unsigned int operatorSort(char op);
ElementType PostfixToInfix(char* expressions,int length);
void reverse(char* s,char* c);

int main(int argc, char** argv)
{
    // char* str = "abc*+de*f+h^g*+";
    char str[] = "abc*+de*f+h^g*+";
    int length = sizeof(str) / sizeof(str[0]);
    char* c = PostfixToInfix(str, length);
    printf("%s\n", c);

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
// pop the top element of the stack
ElementType Top(Stack S)
{
    return S->Array[S->TopOfStack];
    // return S->Array;
}
// Implement operator precedence
unsigned int operatorSort(char op)
{
    unsigned int priority;
    if(op == '^')
       priority = 3;
    else if (op == '*'||op=='/')
       priority = 2;
    else if(op=='+'||op=='-')
       priority = 1;
    else if(op=='(')
       priority = 0;
    return priority;
}
//  postfix expressions convert Infix expressions
ElementType PostfixToInfix(char* expressions, int length)
{
    Stack S = CreatStack(10);
    for (int i = 0; i < length - 1; i++)
    {
        if ((expressions[i] >= 'a' && expressions[i] <= 'z') || (expressions[i] >= '0' && expressions[i] <= '9')
            || (expressions[i] >= 'A' && expressions[i] <= 'Z'))//is number or letter Push stack
        {
            char* str = malloc(sizeof(char) * 100);
            str[0] = expressions[i], str[1] = '\0';
            Push(S, str);
        }
        else
        {
            char ch[100] = "(";
            char* str = malloc(sizeof(char) * 2);
            str[0] = expressions[i],str[1] = '\0';
            //spilc the expressions
            strcat(ch, Top(S));
            free(Pop(S));

            strcat(ch, str);
            free(str);

            strcat(ch,Top(S));

            strcat(ch, ")");
            strcpy(Top(S), ch);
        }
    }
    char* c = Top(S);
    Pop(S);
    clearStack(S);
    char s[100] = {0};//teh temp string
    reverse(c,s);//reverse the string
    return c;
}
// reverse the string
void reverse(char* c,char* s)
{
    for (int i = strlen(c)-1,j = 0; i>=0 ; i--,j++)
    {
        s[j] = c[i];
        if (s[j] == '(') s[j] = ')';
        else if (s[j] == ')') s[j] = '(';
    }
    
    for (int i = 0; i < strlen(c); i++)
    {
        c[i] = s[i];
    }
}