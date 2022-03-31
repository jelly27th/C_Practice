#include <stdio.h>
#include <stdlib.h>

typedef struct Node* ptrToNode;
typedef ptrToNode List;
typedef struct Node** Position;
struct Node {
    int num;
    List next;
};

int FindNode(int pos, List head);
void PrintNode(List head, int* arr);
List CreateNode(int element, Position head, List L);
void PrintLots(List L, List P);
void DeleteNode(List head);

int main(int argc, char** argv)
{
    int P_arr[] = { 1,3,4,6 };
    int L_arr[] = { 1,2,3,4,5,6,7,8,9 };
    List L = malloc(sizeof(struct Node));
    List P = malloc(sizeof(struct Node));
    List P_head = malloc(sizeof(struct Node));
    List L_head = malloc(sizeof(struct Node));
    P_head = NULL;
    L_head = NULL;
    //创建两个链表P L
    for (int i = 0; i < sizeof(P_arr) / sizeof(P_arr[0]); i++)
    {
        P = CreateNode(P_arr[i], &P_head, P);
    }
    for (int i = 0; i < sizeof(L_arr) / sizeof(L_arr[0]); i++)
    {
        L = CreateNode(L_arr[i], &L_head, L);
    }

    PrintLots(L_head, P_head);

    DeleteNode(P_head);
    DeleteNode(L_head);
    return 0;
}

//找到相应位置的节点
int FindNode(int pos, List head)
{
    int count = 1;
    List point = head;
    while (point != NULL)
    {
        if (count == pos)
        {
            int temp = point->num;
            //free(point);
            return temp;
        }
        point = point->next;
        count++;
    }
    return -1;
}
//打印链表并返回数组
void PrintNode(List head, int* arr)
{
    int i = 0;
    List pos = head;
    while (pos != NULL)
    {
        arr[i++] = pos->num;
        pos = pos->next;
    }
    free(pos);
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
//在L的元素中找出P对应位置的元素
void PrintLots(List L, List P)
{
    int arr[4] = { 0 };
    PrintNode(P, arr);

    for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
    {
        printf("%d ", FindNode(arr[i], L));
    }
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