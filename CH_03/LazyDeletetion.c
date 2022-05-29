/**
 * @file LazyDeletetion.c
 * @author Jelly (wugd827@163.com)
 * @brief 习题3.17
 * @version 0.1
 * @date 2022-05-24
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node* ptrToNode;
typedef ptrToNode List;
// typedef struct Node** Position;
typedef ptrToNode Position;
struct Node {
    int num;
    List next;
    bool flag;
};

List Header(int element);
void Insert(int element, Position head);
void Print(List head);
int RealLength(List head);
int FakeLength(List head);
void Delete(int element,List head);
void RealDelete(List head);

int main(int argc, char** argv)
{
    int arr[] = {0, 1, 2, 3, 4, 5};
    List head = Header(arr[0]);
    int length = sizeof(arr) / sizeof(arr[0]);
    for(int i = 1;i< length; i++)
    {
        Insert(arr[i],head);
    }
    Print(head);
    printf("\n");

    Delete(3, head);
    Print(head);
    printf("\n");

    Delete(1, head);
    Print(head);
    printf("\n");

    Delete(5, head);
    Print(head);
    printf("\n");
    
    Delete(4, head);
    Print(head);
    printf("\n");

    Delete(0, head);
    Print(head);
    printf("\n");

    Delete(2, head);
    return 0;
}
//create a head node
Position Header(int element)
{
    List head = malloc(sizeof(struct Node));
    head->num = element;
    head->next = NULL;
    head->flag = false;
    return head;
}
// insert a Node
void Insert(int element, Position head)
{
    List pos = head;
    while(pos->next != NULL) 
          pos = pos->next;

    List temp = malloc(sizeof(struct Node));
    temp->next = NULL;
    temp->flag = false;
    temp->num = element;

    pos->next = temp;
}
// print the list of elements
void Print(List head)
{
    if(head == NULL) printf("no list\n");

    List pos = head;
    while(pos!= NULL)
    {
        if(pos->flag==false) 
        printf("%d ", pos->num);
        pos = pos->next;
    }

         
}
// the real length of the list
int RealLength(List head)
{
    List pos = head;
    int length = 0;
    while(pos!= NULL)
    {
        length++;
        pos = pos->next;
    }
    return length;
}
// the legth of the list by deleting
int FakeLength(List head)
{
    List pos = head;
    int length = 0;
    while(pos!= NULL)
    {
        if(pos->flag==true) length++;
        pos = pos->next;
    }
    return length;
}
//delete the element at the list 
void Delete(int element,List head)
{
    List pos = head;
    while(pos!=NULL)
    {
        if(pos->num==element) 
        {
            pos->flag =true;
            break;
        }
        pos = pos->next;
    }
    int Fakelength = FakeLength(head);
    int Reallength = RealLength(head);
    if(Reallength==Fakelength)
    {
        RealDelete(head);
    }
}
// delete the list really
void RealDelete(List head)
{
    while(head!=NULL)
    {
        List temp = head;
        head = head->next;
        free(temp);
    }
}