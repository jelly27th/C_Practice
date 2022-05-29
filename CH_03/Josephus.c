/**
 * @file Josephus.c
 * @author Jelly (wugd827@163.com)
 * @brief Exercise 3.10
 * @version 0.1
 * @date 2022-05-29
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<windows.h>

typedef struct Node* ptrToNode;
typedef ptrToNode List;
typedef struct Node** Position;
struct Node {
	int num;
	List next;
};

void Josephus(int* arr,int length, int N);
#define NUM 20000

int main(int argc, char **argv)
{
    int arr[NUM] = {0};
    for (int i = 0;i<=NUM;i++)
    {
        arr[i] = i+1;
    }
    int length = sizeof(arr) / sizeof(arr[0]);
    clock_t start, finish;  
    double  duration; 
    start = clock(); 
    Josephus(arr,length,1);
    finish = clock();  
    duration = (double)(finish - start) / CLOCKS_PER_SEC;  
    printf( "%f seconds\n", duration ); 
    return 0;
}
//循环链表解决约瑟夫问题 O(MN)
void Josephus(int* arr,int length, int N)
{
    List pos = malloc(sizeof(struct Node));
    pos->num = arr[0];
    pos->next = pos;
    for (int i = 1; i < length; i++)
    {
        List temp = malloc(sizeof(struct Node));
        temp->num = arr[i];
        temp->next = pos->next;
        pos->next = temp;
        pos = temp;
    }
    int total = length-1;
    pos = pos->next;
    while(total--)
    {
        for(int i = 0; i <N-1;i++ )
        {
            pos = pos->next;
        }
        List temp = pos->next;
        pos->next = pos->next->next;
        pos = pos->next;
        free(temp);
    }
    printf("%d\n",pos->num);
    free(pos);
}