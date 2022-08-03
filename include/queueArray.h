#ifndef _QUEUEARRAY_H
#define _QUEUEARRAY_H
#include <stdbool.h>

#define FrontInit 0;
#define RearInit 0;
typedef int ElementType;
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
ElementType Front(Queue queue);
bool IsEmpty(Queue queue);
bool IsFull(Queue queue);
void MakeEmpty(Queue queue);
void ClearQueue(Queue queue);

#endif