/**
 * @file LinkedList.c
 * @author Jelly (wugd827@163.com)
 * @brief Exercise 3.1
 * @version 0.1
 * @date 2022-05-29
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct Node *ptrToNode;
typedef ptrToNode List;
typedef struct Node **Position;
struct Node {
    int num;
    List next;
};

void PrintNode(List head);
List CreateNode(int element,Position head,List L);

int main(int argc, char **argv)
{
    int arr[] = {1,2,3,4,5,6,7,8,9};
    List L = malloc(sizeof(struct Node));
    List head = malloc(sizeof(struct Node));
    head = NULL;
    for (int i = 0; i < 9;i++)
    {
	   L = CreateNode(arr[i],&head,L);
    }
    PrintNode(head);
    free(head);
    free(L);
    return 0;
}
//打印链表
void PrintNode(List head)
{
    List pos = head;
    while(pos != NULL)
    {
        printf("%d\n",pos->num);
        pos = pos->next;
    }
}
//创建节点
List CreateNode(int element,Position head,List L)
{
    List temp = malloc(sizeof(struct Node));
    temp->num = element;
    temp->next = NULL;
    if(*head==NULL)
    {
        *head = L =temp;
    }
    else
    {
        L->next = temp;
        L = temp;
    }
    return L;
}