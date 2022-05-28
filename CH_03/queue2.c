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

typedef int ElementType;
typedef struct _queue queue;
typedef queue* Queue; 

struct _queue{
    int Capacity;
    int front;
    int rear;
    ElementType* Array;
};

int main(int argc, char **argv)
{
    return 0;
}