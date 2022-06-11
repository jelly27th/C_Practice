/**
 * @file deque.c
 * @author Jelly (wugd827@163.com)
 * @brief Exercise 3.26 
 *        this is a problem,No matter whether the head of the team or the tail of the team 
 *        can't prevent the queue from overflowing
 * @version 0.1
 * @date 2022-05-28
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct _deque deque;
typedef deque* Deque;
#define RearInit 1
#define FrontInit 0

struct _deque{
    int Capacity;
    // int size;
    int rear;
    int front;
    ElementType *Array;
};
Deque EmptyDeque(int MaxDequeSize);
void MakeEmpty(Deque deque);
bool Push(Deque deque,ElementType element);
bool Pop(Deque deque);
ElementType Front(Deque deque);
bool Insert(Deque deque, ElementType element);
bool Eject(Deque deque);
ElementType Rear(Deque deque);
bool IsEmpty(Deque deque);
bool IsFull(Deque deque);


int main(int argc, char** argv)
{
    Deque deque = EmptyDeque(10);
    Push(deque,10);
    Push(deque,22);
    printf("%d\n",Front(deque));
    Pop(deque);
    printf("%d\n",Front(deque));
    // Pop(deque);

    Insert(deque,0);
    Insert(deque,1);
    printf("%d\n",Rear(deque));
    Eject(deque);
    printf("%d\n",Rear(deque));
    Eject(deque);
    // Eject(deque);
    return 0;
}
// create a empty deque
Deque EmptyDeque(int MaxDequeSize)
{
    Deque deque = malloc(sizeof(deque));
    deque->Array = malloc(sizeof(ElementType)*MaxDequeSize);
    deque->Capacity = MaxDequeSize;
    MakeEmpty(deque);
    return deque;
}
// empty the deque
void MakeEmpty(Deque deque)
{
    deque->front = FrontInit;
    deque->rear = RearInit;
}
// insert element at front of deque
bool Push(Deque deque,ElementType element)
{
    if(IsFull( deque))
    {
        printf("Push:the deque already full\n");
        return false;
    }
    else
    {
        deque->Array[deque->front] = element;
        deque->front = (deque->front-1+deque->Capacity)%deque->Capacity;
    }
    return true;
}
// delete the front element from front of deque
bool Pop(Deque deque)
{
    if(IsEmpty( deque))
    {
        printf("Pop:the front of deque already empty\n");
        return false;
    }
    else{
        deque->front = (deque->front + 1) % deque->Capacity;
    }
    return true;
}
// display the front element of the deque
ElementType Front(Deque deque)
{
    return deque->Array[(deque->front+1)%deque->Capacity];
}
// insert element at the end of the deque
bool Insert(Deque deque, ElementType element)
{
    if(IsFull( deque))
    {
        printf("Insert:the deque already full\n");
        return false;
    }
    else
    {
        deque->Array[deque->rear] = element;
        deque->rear = (deque->rear + 1) % deque->Capacity;
    }
    return true;
}
// delete the end of element from teh end of deque
bool Eject(Deque deque)
{
    if(IsEmpty( deque))
    {
        printf("Eject:the end of deque already empty\n");
        return false;
    }
    else{
        deque->rear = (deque->rear-1+deque->Capacity)% deque->Capacity;
    }
    return true;
}
// display the end of element from the queue
ElementType Rear(Deque deque)
{
    return deque->Array[(deque->rear-1+deque->Capacity)% deque->Capacity];
}
// check if the deque is empty
bool IsEmpty(Deque deque)
{
    return (deque->front+1)% deque->Capacity==deque->rear;
}
// check if the deque is full
bool IsFull(Deque deque)
{
    return (deque->rear+1)% deque->Capacity==deque->front;
}