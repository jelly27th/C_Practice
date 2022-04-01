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
void PrintNode(List head);
int Length(List head);
void Intersection(List head1,List head2,int* arr);

int main(int argc, char** argv)
{
    int P_arr[] = { 1,3,4,6,11};
    int L_arr[] = { 1,2,3,4,5,6,7,8,9 };
    List L = malloc(sizeof(struct Node));
    List P = malloc(sizeof(struct Node));
    List P_head = NULL;
    List L_head = NULL;
    //创建两个链表P L
    for (int i = 0; i < sizeof(P_arr) / sizeof(P_arr[0]); i++)
    {
        P = CreateNode(P_arr[i], &P_head, P);
    }
    PrintNode(P_head);
    for (int i = 0; i < sizeof(L_arr) / sizeof(L_arr[0]); i++)
    {
        L = CreateNode(L_arr[i], &L_head, L);
    }
    PrintNode(L_head);
    int arr[4] = { 0};
    Intersection(P_head, L_head,arr);
    List K = malloc(sizeof(struct Node));
    List head = NULL;
    for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
    {
        K = CreateNode(arr[i], &head, K);
    }
    PrintNode(head);
    DeleteNode(head);
    DeleteNode(P_head);
    DeleteNode(L_head);
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
    List temp = head;
    while (temp != NULL)
    {
        head = head->next;
        free(temp);
        temp = head;
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
}
//统计链表长度
int Length(List head)
{
    List pos = head;
    int length = 0;
    while(pos != NULL)
    {
        pos = pos->next;
        length++;
    }
    return length;
}
//链表交集
void Intersection(List head1,List head2,int* arr)
{
    List pos1 = head1;
    List pos2 = head2;
    int i = 0;
    if(Length(head1)>=Length(head2))
    {
        while(pos1!= NULL)
        {
            if(pos2->num==pos1->num)
            {
                arr[i++] = pos1->num;
                pos2 = pos2->next;
            }
            pos1 = pos1->next;
        }
    }
    else
    {
        while(pos2!= NULL)
        {
            if(pos2->num==pos1->num)
            {
                arr[i++] = pos1->num;
                pos1 = pos1->next;
            }
            pos2= pos2->next;
        }
    }
}