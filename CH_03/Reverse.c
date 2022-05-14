/**
 * @file Reverse.c
 * @author 吴国栋 (872908391@qq.com)
 * @brief 习题3.12
 * @version 0.1
 * @date 2022-05-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct Node* ptrToNode;
typedef ptrToNode List;
typedef struct Node** Position;
struct Node {
    int num;
    List next;
};
List CreateNode(int element,Position head,List L);
void PrintNode(List head);
void DeleteNode(List head);
List Reverse(List head);

int main(int argc, char **argv)
{
    int arr[] = {1,2,3,4,5,6,7,8,9};
    List L = malloc(sizeof(struct Node));
    List head = NULL;
    //创建链表L
    for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
    {
        L = CreateNode(arr[i], &head, L);
    }
    head = Reverse(head);
    PrintNode(head);
    DeleteNode(head);
    return 0;
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
//删除节点
void DeleteNode(List head)
{
    List temp = head;
    while (temp != NULL)
    {
        head = head->next;
        free(temp);
        temp = head;
    }
}
//反转单链表 双指针迭代法
List Reverse(List head)
{
    if(head == NULL||head->next == NULL)
    {
        return head;
    }

    List cur = head;
    List pre = NULL;
    while (cur != NULL)
    {
        List temp = cur->next;
        cur->next = pre;
        pre = cur;  
        cur = temp;
    }
    return pre;
}