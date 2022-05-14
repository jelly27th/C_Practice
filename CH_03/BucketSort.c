/**
 * @file BucketSort.c
 * @author 吴国栋 (872908391@qq.com)
 * @brief 习题3.13
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
List CreateNode(int element,List head);
void PrintNode(List head);
void DeleteNode(List head);
void BucketSort(int *arr,int length);
int three(int num, int n);
int Length(List head);

int main(int argc, char **argv)
{
    int arr[] = {678912345,234567891,123456789,567891234,678912345,234567891,123456789,567891234,678912345,234567891,123456789,567891234};
    int length = sizeof(arr) / sizeof(arr[0]);
    BucketSort(arr,length);
    return 0;
}

//创建节点
List CreateNode(int element,List head)
{
    if(head->next==NULL&&head->num==0)
    {
        head->num = element;
    }
    else
    {
        List temp = malloc(sizeof(struct Node));
        temp->num = element;
        temp->next = NULL;
        List pos = head;
        while(pos->next != NULL)
        {
            pos = pos->next;
        }
        pos->next = temp;
    }
    return head;
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
//桶排序
void BucketSort(int *arr,int length)
{
    struct Node stu[1000];
    //结构体数组初始化
    for (int i = 0; i <1000;i++)
    {
        stu[i].next = NULL;
        stu[i].num = 0;
    }
    for (int n = 0; n <3;n++)
    {
        //放入桶中
        for (int i = 0; i <length;i++)
        {
            CreateNode(arr[i],&stu[three(arr[i],n)]);
        }
        //重新放入数组arr
        int k = 0;
        for (int i = 0; i <1000;i++)
        {
            //如果桶中有数
            if(stu[i].num!=0)
            {
                List head = &stu[i]; 
                while(head!=NULL)
                {
                    arr[k++] = head->num;
                    head = head->next;
                }
                //初始化有数的桶
                head = &stu[i];
                if(Length(head)==1)
                {
                    stu[i].next = NULL;
                    stu[i].num = 0;
                }
                else{
                    DeleteNode(head->next);
                    stu[i].next = NULL;
                    stu[i].num = 0;
                }
            }
        }

    }
    for (int i = 0; i <length; i++)
    {
        printf("%d ",arr[i]);
    }
}
//取三位数
int three(int num, int n)
{
    for (int i = 0; i <n;i++)
        num = num/1000;
    return num %1000;
}
//统计链表长度
int Length(List head)
{
	List pos = head;
	int length = 0;
	while (pos != NULL)
    {
        pos = pos->next;
        length++;
    }
	return length;
}