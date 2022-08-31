#ifndef _QUEUEARRAY_H
#define _QUEUEARRAY_H
#include <stdbool.h>
#include "AvlTree.h"

#define FrontInit 0;
#define RearInit 0;
/*
default
*/
// typedef int ElementType;
/*
exercise 4.33
*/
typedef AvlTree ElementType;

typedef struct _queue queue;
typedef queue* Queue; 

struct _queue{
    int Capacity;
    int front;
    int rear;
    int size;
    ElementType* Array;
};
Queue EmptyQueue(int MaxQueueSize);
bool Enqueue(Queue queue,ElementType element);
bool Dequeue(Queue queue);
ElementType QueueFront(Queue queue);
bool QueueIsEmpty(Queue queue);
bool QueueIsFull(Queue queue);
void QueueMakeEmpty(Queue queue);
void ClearQueue(Queue queue);

#endif