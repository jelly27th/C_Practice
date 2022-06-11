/**
 * @file queue2.c
 * @author Jelly (wugd827@163.com)
 * @brief Exercise 3.25(b)
 * @version 0.1
 * @date 2022-05-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

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


int main(int argc, char **argv)
{
    Queue queue = EmptyQueue(10);
    Enqueue(queue,11);
    Enqueue(queue,2);
    Enqueue(queue,3);
    printf("%d\n",Front(queue));
    Dequeue(queue);
    printf("%d\n",Front(queue));
    Dequeue(queue);
    printf("%d\n",Front(queue));
    Dequeue(queue);
    Dequeue(queue);
    ClearQueue(queue);
    return 0;
}

// create a queue of a array
Queue EmptyQueue(int MaxQueueSize)
{
    Queue queue = malloc(sizeof(queue));
    // queue->Array = malloc(sizeof(ElementType)*(MaxQueueSize+1));
    queue->Array = malloc(sizeof(ElementType)*(MaxQueueSize));
    queue->Capacity = MaxQueueSize;
    MakeEmpty(queue);
    return queue;
}
// insert an element from the queue of a array
bool Enqueue(Queue queue,ElementType element)
{
    if(IsFull(queue)) 
    {
        printf("the queue is already empty\n");
        return false;
    }
    else 
    {
        queue->Array[queue->rear] = element;
        queue->rear = queue->rear + 1>=queue->Capacity? 0 : queue->rear+1;
        queue->size++;
    }
    return true;
}
// out an element from the queue of a array
bool Dequeue(Queue queue)
{
    if(IsEmpty(queue))
    {
        printf("the queue is already empty\n");
        return false;
    }
    else
    {
        queue->front = queue->front+1>=queue->Capacity? 0 : queue->front+1;
        queue->size--;
    } 
    return true;
}
// display the front element of the queue
ElementType Front(Queue queue)
{
    return queue->Array[queue->front];
}
// check if the queue is empty
bool IsEmpty(Queue queue)
{
    return queue->size==0;
}
// check if the queue is full
bool IsFull(Queue queue)
{
    return queue->size==queue->Capacity;
}
// empty the queue
void MakeEmpty(Queue queue)
{
    queue->front = FrontInit;
    queue->rear = RearInit;
    queue->size = 0;
}
// delete the queue
void ClearQueue(Queue queue)
{
    free(queue->Array);
    free(queue);
}