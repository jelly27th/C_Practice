/**
 * @file SelfAdujstmentTable.c
 * @author 吴国栋 (872908391@qq.com)
 * @brief 习题3.15
 * @version 0.1
 * @date 2022-05-23
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
List CreateNode(int element,Position head,List L);
void PrintNode(List head);
void DeleteNode(List head);
void FindList(List head,int element);
List Find(List head,int element);
List Insert(List pos,int element);
void Delete(List head,int element);
List FindPrevious(List head,int element);

void FindArray(int* arr,int length, int element);

int main(int argc, char** argv)
{
    int arr[] = {1,2,3,4,5,6,7,8,9};
    //数组自调整表
    // int length = sizeof(arr) / sizeof(arr[0]);
    // FindArray(arr, length, 5);
    // for (int i = 0; i < length; i++)
    // printf("%d ",arr[i]);

    //链表自调整表
    List L = malloc(sizeof(struct Node));
    List head = NULL;
    //创建链表L
    for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
    {
        L = CreateNode(arr[i], &head, L);
    }
    FindList(head,5);
    // PrintNode(head);
    DeleteNode(head);
    return 0;
}
//数组自调整表的实现
// 1-2-3-4-5-6 
//you need to find 4
//the result is 4-1-2-3-5-6 
void FindArray(int* arr,int length, int element)
{
    int pos = -1;
    for (int i = 0; i < length; i++)
    {
        if(element == arr[i])
        {
            pos = i;
            break;
        }
    }
    if(pos!=-1)
    {
        for(int i = pos;i>0;i--)
        {
            arr[i] = arr[i-1];
        }
        arr[0] = element;
    }
    if(pos==-1) printf("No Find!\n");
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
// 链表自调整表的实现
void FindList(List head,int element)
{
    // List pos = Find(head,element);//找到元素所在位置
    Delete(head,element);//删除节点
    head = Insert(head,element);//头插法
    PrintNode(head);
}
//找到元素所在位置
List Find(List head,int element)
{
    List pos = head;
    while(pos!= NULL)
    {
        if(pos->num==element) return pos;
        pos = pos->next;
    }
    return NULL;
}
List FindPrevious(List head,int element)
{
    List pos = head;
    while(pos!= NULL)
    {
        if(pos->next->num==element) return pos;
        pos = pos->next;
    }
    return NULL;
}
void Delete(List head,int element)
{
    List prev = FindPrevious(head,element);
    List pos = Find(head,element);
    prev->next = pos->next;
    free(pos);
}
List Insert(List pos,int element)
{
    List temp = malloc(sizeof(struct Node));
    temp->next = NULL;
    temp->num = element;

    temp->next = pos;

    return temp;
}