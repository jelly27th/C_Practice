#include "queueArray.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

// create a queue of a array
Queue EmptyQueue(int MaxQueueSize)
{
    Queue queue = malloc(sizeof(queue));
    // queue->Array = malloc(sizeof(ElementType)*(MaxQueueSize+1));
    queue->Array = malloc(sizeof(ElementType)*(MaxQueueSize));
    queue->Capacity = MaxQueueSize;
    QueueMakeEmpty(queue);
    return queue;
}
// insert an element from the queue of a array
bool Enqueue(Queue queue,ElementType element)
{
    if(QueueIsFull(queue)) 
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
    if(QueueIsEmpty(queue))
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
ElementType QueueFront(Queue queue)
{
    return queue->Array[queue->front];
}
// check if the queue is empty
bool QueueIsEmpty(Queue queue)
{
    return queue->size==0;
}
// check if the queue is full
bool QueueIsFull(Queue queue)
{
    return queue->size==queue->Capacity;
}
// empty the queue
void QueueMakeEmpty(Queue queue)
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