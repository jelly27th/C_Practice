/**
 * @file convert.c
 * @author Jelly (wugd827@163.com)
 * @brief Exercise 3.20(a) and 3.20(b) 
 * @version 0.1
 * @date 2022-05-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define EmptyTOS -1
#define STACK_SIZE 10
typedef char ElementType;
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
void InfixToPostfix(char* expressions,int length);

int main(int argc, char **argv)
{
    char str[] = "a+b*c+(d*e+f)^h*g";
    int len = sizeof(str)/ sizeof(str[0]);
    
    InfixToPostfix(str,len); 
    printf("%s\n",str);
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
}
// Infix expressions convert postfix expressions
void InfixToPostfix(char* expressions,int length)
{
    char output[length];
    Stack S = CreatStack(STACK_SIZE);
    int j = 0;
    for(int i=0;i<length-1;i++)
    {
        if((expressions[i]>='a'&&expressions[i]<='z')||(expressions[i]>='0'&&expressions[i]<='9')
        ||(expressions[i]>='A'&&expressions[i]<='Z'))//is number or letter output
           output[j++] = expressions[i];
        else//not number or letter
        {
            if(IsEmpty(S)) Push(S,expressions[i]); //the stack is empty push stack
            else if(expressions[i]=='(') Push(S,expressions[i]);// is '(' push stack
            else if(expressions[i]==')') //is ')' pop stack when top is ')' stop
            {
                while(Top(S)!='(')
                {
                    output[j++] = Pop(S);
                }
                Pop(S);
            }
            else 
            {
                while(operatorSort(expressions[i])<=operatorSort(Top(S)))
                {
                    output[j++] = Pop(S);
                    if(IsEmpty(S)) break;//when the stack is empty break the loop
                }
                Push(S,expressions[i]);
            }
        }
    }
    while(!IsEmpty(S)) output[j++] = Pop(S);
    output[j] = '\0';
    for (int i = 0; i <length; i++)
        expressions[i] = output[i];
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