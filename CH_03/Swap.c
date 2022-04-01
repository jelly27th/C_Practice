#include <stdio.h>
#include <stdlib.h>

/***** 单链表****/
typedef struct Node* ptrToNode;
typedef ptrToNode List;
typedef struct Node** Position;
struct Node {
    int num;
    List next;
};

List CreateNode(int element, Position head, List L);
void DeleteNode(List head);
List SwapNode(List position,List head);
void PrintNode(List head);
List FindPreviousNode(List L,List head);
/***** 单链表****/

/***** 双链表****/
typedef struct DoubleNode* DoubleptrToNode;
typedef DoubleptrToNode DoubleList;
typedef struct DoubleNode** DoublePosition;
struct DoubleNode {
    int num;
    DoubleList next;
    DoubleList prev;
};

DoubleList CreateDoubleNode(int element,DoublePosition pos);
void PrintDoubleNode(DoubleList pos);
void DeleteDoubleNode(DoubleList pos);
DoubleList SwapDoubleNode(DoubleList pos,DoubleList start);
/***** 双链表****/

int main(int argc, char** argv)
{
    int arr[] = {1,2,3,4,5,6,7,8,9};
    /***单链表****/
    // List L = malloc(sizeof(struct Node));
    // List head = malloc(sizeof(struct Node));
    // head = NULL;
    // for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
    // {
    //     L = CreateNode(arr[i],&head,L);
    // }
    // head = SwapNode(head->next,head);
    // PrintNode(head);
    // DeleteNode(head);
    /***单链表****/

    /*****双链表****/
    DoubleList pos = malloc(sizeof(struct DoubleNode));
    pos = NULL;
    for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
    {
        pos = CreateDoubleNode(arr[i],&pos);
    }
    pos = SwapDoubleNode(pos->prev,pos);
    PrintDoubleNode(pos);
    DeleteDoubleNode(pos);
    /*****双链表****/
    return 0;
}

/***** 单链表****/
//创建节点
List CreateNode(int element, Position head, List L)
{
    List temp = malloc(sizeof(struct Node));
    temp->num = element;
    temp->next = NULL;
    if (*head == NULL)
    {
        *head = L = temp;
    }
    else
    {
        L->next = temp;
        L = temp;
    }
    return L;
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
//交换相邻节点并返回头节点
List SwapNode(List pos, List head)
{
    if(pos->next==NULL)
       return head;
    if(head == pos)
    {
        List pos1 = pos->next;
        List pos2 = pos1->next;

        pos1->next = pos;
        pos->next = pos2;
        head = pos1;
        return head;
    }
    else
    {
        List prev = FindPreviousNode(pos, head);
        List pos1 = pos->next;
        List pos2 = pos1->next;

        pos1->next = pos;
        pos->next = pos2;
        prev->next = pos1;
        return head;
    }

}
//找上一个节点
List FindPreviousNode(List L,List head)
{
    List temp = head;
    while (temp != NULL)
    {
        if (temp->next ==L)
            return temp;
        temp = temp->next;
    }
    return NULL;
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
/***** 单链表****/

/***** 双链表****/

//创建双链表节点
DoubleList CreateDoubleNode(int element,DoublePosition pos)
{
    DoubleList temp = malloc(sizeof(struct DoubleNode));
    temp->num = element;
    temp->next = NULL;
    temp->prev = NULL;
    if(*pos == NULL)
    {
        *pos = temp;
    }
    else
    {
        (*pos)->next = temp;
        temp->prev = *pos;
    }
    return temp;
}
//打印双链表
void PrintDoubleNode(DoubleList pos)
{
    DoubleList temp = pos;
    if(temp->next == NULL)
    {
        while(temp!= NULL)
        {
            printf("%d\n", temp->num);
            temp = temp->prev;
        }
    }
    else if(temp->prev == NULL)
    {
        while(temp!= NULL)
        {
            printf("%d\n", temp->num);
            temp = temp->next;  
        }
    }
}
//删除双链表
void DeleteDoubleNode(DoubleList pos)
{
    DoubleList temp = pos;
    if(temp->next == NULL)
    {
        while(temp!= NULL)
        {
            pos = pos->prev;
            free(temp);
            temp = pos;
        }
    }
    else if(temp->prev == NULL)
    {
        while(temp!= NULL)
        {
            pos = pos->next;
            free(temp);
            temp = pos; 
        }
    }
}
DoubleList SwapDoubleNode(DoubleList pos,DoubleList start)
{
    //只有一个节点
    if(start->next == NULL&&start->prev == NULL)
       return start;
    //有多个节点
    if(pos==start)
    {
        if(pos->prev == NULL)
        {
            DoubleList pos1 = pos->next;
            DoubleList pos2 = pos1->next;

            pos->next = pos2;
            pos->prev = pos1;
            pos1->next = pos;
            pos1->prev =NULL;
            pos2->prev = pos;

            start = pos1;
            return start;
        }
        else if(pos->next == NULL)
        {
            DoubleList pos1 = pos->prev;
            DoubleList pos2 = pos1->prev;

            pos->next = pos1;
            pos->prev = pos2;
            pos1->next = NULL;
            pos1->prev = pos;
            pos2->next = pos;

            start = pos1;
            return start;
        }
    }
    else//处于中间交换
    {
        DoubleList pos1 = pos->prev;
        DoubleList pos2 = pos1->prev;
        DoubleList prev = pos->next;

        prev->prev = pos1;
        pos1->next = prev;
        pos1->prev = pos;
        pos->next = pos1;
        pos->prev = pos2;
        pos2->next = pos;

        return start;
    }
    return NULL;
}
/***** 双链表****/