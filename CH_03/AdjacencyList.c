/**
 * @file AdjacencyList.c
 * @author 吴国栋 (872908391@qq.com)
 * @brief 习题3.14
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
List CreateNode(int element, List head);
void PrintNode(List head);
void DeleteNode(List head);
void AdjacencyList(int(*graph)[5], int row, int col, List stu);

int main(int argc, char** argv)
{
    int graph[5][5] = {
        {0,1,1,0,1},
        {1,0,1,0,0},
        {1,1,0,1,0},
        {0,0,1,0,1},
        {1,0,0,1,0}
    };
    int col = sizeof(graph[0]) / sizeof(graph[0][0]);//列
    int row = sizeof(graph) / sizeof(graph[0]);//行
    struct Node stu[5];
    //结构体数组初始化
    for (int i = 0; i < row; i++)
    {
        stu[i].num = i;
        stu[i].next = NULL;
    }
    AdjacencyList(graph, row, col, &stu);
    //画图
    int draw[5][5] = { 0 };
    for (int i = 0; i < row; i++)
    {
        List head = stu[i].next;
        while (head != NULL)
        {
            draw[i][head->num] = 1;
            head = head->next;
        }
    }
    //显示图
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            printf("%d ", draw[i][j]);
        }
    }
    for (int i = 0; i < row; i++)
        DeleteNode(stu[i].next);
    return 0;
}

//创建节点
List CreateNode(int element, List head)
{
    List temp = malloc(sizeof(struct Node));
    temp->num = element;
    temp->next = NULL;
    if (head->next == NULL)
    {
        head->next = temp;
    }
    else
    {
        List pos = head->next;
        while (pos->next != NULL)
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
    while (pos != NULL)
    {
        printf("%d\n", pos->num);
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
//链表实现邻接表
void AdjacencyList(int(*graph)[5], int row, int col, List stu)
{
    //邻接表
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (graph[i][j] == 1)
            {
                CreateNode(j, stu + i);
            }
        }
    }
}