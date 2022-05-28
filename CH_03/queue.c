/**
 * @file queue.c
 * @author Jelly (wugd827@163.com)
 * @brief Exercise 3.25(a)
 * @version 0.1
 * @date 2022-05-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct _node* Node;
typedef struct _node  node;
typedef struct _queue* Queue;
typedef struct _queue queue;

struct _node{
    ElementType data;
    Node next;
};
struct _queue{
    Node front;
    Node rear;
};
Queue EmptyQueue();
void Enqueue(ElementType data,Queue queue);
void Dequeue(Queue queue);
bool IsEmpty(Queue queue);
void MakeEmpty(Queue queue);
void ClearQueue(Queue queue);
void PrintQueue(Queue queue);

int main(int argc, char **argv)
{
    Queue queue = EmptyQueue();
    Enqueue(1, queue);
    Enqueue(9, queue);
    Enqueue(7, queue);
    PrintQueue(queue);
    Dequeue(queue);
    Dequeue(queue);
    PrintQueue(queue);
    ClearQueue(queue);
    return 0;
}

// create a empty queue
Queue EmptyQueue()
{
    Queue queue =  malloc(sizeof(queue));
    queue->rear = queue->front = malloc(sizeof(node));
    return queue;
}
// insert an element from the queue
void Enqueue(ElementType data,Queue queue)
{
    queue->rear->next = malloc(sizeof(node));
    queue->rear = queue->rear->next;
    queue->rear->data = data;
    queue->rear->next = NULL;
}
// out an element from the queue
void Dequeue(Queue queue)
{
    Node temp = queue->front->next;
    queue->front->next = temp->next;
    if(temp==queue->rear) queue->rear = queue->front;
    free(temp);
}
// check if the queue is empty
bool IsEmpty(Queue queue)
{
    if(queue->front==queue->rear) return true;
    else return false;
}
// clear the queue
void ClearQueue(Queue queue)
{
    MakeEmpty(queue);
    free(queue->front);
}
// make queue empty
void MakeEmpty(Queue queue)
{
    while(queue->front!=queue->rear)
        Dequeue(queue);
}
// print all elements from the queue
void PrintQueue(Queue queue)
{
    Node pos = queue->front->next;
    while(pos!=queue->rear)
    {
        printf("%d ", pos->data);
        pos = pos->next;
    }
    printf("%d\n",pos->data);
}