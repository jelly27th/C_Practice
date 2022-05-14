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

List CreateNode(int element,Position head,List L);
List FindNode(int Element, List head);
List ReFindNode(int Element, List head);
void PrintNode(List head);

#define NUM 40201

int main(int argc, char** argv)
{
    int arr[NUM] = {0};
    for (int i = 0;i<NUM;i++)
    {
        arr[i] = i+1;
    }
    List L = malloc(sizeof(struct Node));
    List head = NULL;
    
    //创建链表L
    for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
    {
        L = CreateNode(arr[i], &head, L);
    }

    clock_t start, finish;  
    double  duration; 
    start = clock(); 
    // List pos = FindNode(299999,head); 
    List pos = ReFindNode(40201,head);
    if (pos != NULL){
        printf("%d\n",pos->num);
    }
    else{
        printf("error\n");
    }
    finish = clock();  
    duration = (double)(finish - start) / CLOCKS_PER_SEC;  
    printf( "%f seconds\n", duration ); 
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
//找到特定元素的节点并返回位置(非递归版)
List FindNode(int Element, List head)
{
    List point = head;
    while (point != NULL)
    {
        if (point->num == Element)
        {
            return point;
        }
        point = point->next;
    }
    return NULL;
}
//找到特定元素的节点并返回位置(递归版)
List ReFindNode(int Element, List head)
{
    if(head)
    {
        if(head->num==Element)
        return head;
        else{
            head = head->next;
            return ReFindNode(Element, head);
        }
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