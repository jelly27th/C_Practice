#include <stdio.h>
#include <stdlib.h>

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

int main(int argc, char** argv)
{
    int arr[] = {1,2,3,4,5,6,7,8,9};
    List L = malloc(sizeof(struct Node));
    List head = malloc(sizeof(struct Node));
    head = NULL;
    for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
    {
        L = CreateNode(arr[i],&head,L);
    }
    head = SwapNode(head,head);
    PrintNode(head);
    DeleteNode(head);
    return 0;
}


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
    List temp = malloc(sizeof(struct Node));
    temp = head;
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
        List pos1 = pos->next;
        List pos2 = pos1->next;

        pos1->next = pos;
        pos->next = pos2;
        return head;
    }

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
    free(pos);
}