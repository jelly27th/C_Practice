/**
 * @file Cursor.c
 * @author 吴国栋 (872908391@qq.com)
 * @brief 习题3.14 b
 * @version 0.1
 * @date 2022-05-15
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <stdio.h>
#include <stdlib.h>

 //游标实现链表定义
#define SpaceSize 100
typedef int ptrToNode;
typedef ptrToNode List;
typedef  ptrToNode Position;
struct Node {
    int num;
    List next;
};

struct Node CursorSpace[SpaceSize];
static Position CursorAlloc();
static void CursorFree(Position P);
void PrinrfCursorList(Position pos);
void DeleteCursorList(Position pos);
Position CreateCursorNode(Position pos, int Element);
void AdjacencyList(int(*graph)[5], int row, int col, Position* stu);
Position CreateCursor(Position head, int Element);

void InitCursor();

int main(int argc, char** argv)
{
    InitCursor();
    /**          0
               / \ \
              1 --\-2
                  /\ |
                3 ---4
    **/
    int graph[5][5] = {
        {0,1,1,0,1},
        {1,0,1,0,0},
        {1,1,0,1,0},
        {0,0,1,0,1},
        {1,0,0,1,0}
    };
    int col = sizeof(graph[0]) / sizeof(graph[0][0]);//列
    int row = sizeof(graph) / sizeof(graph[0]);//行
    /***游标链表实现***/
    // int arr[] = {0,1,2,3,4,5};
    // Position head = CursorAlloc();
    // Position pos = head;
    // for (int i = 0; i <6;i++)
    // {
    //     pos = CreateCursorNode(pos,arr[i]);
    // }
    /***游标链表实现***/

    Position stu[5] = { 0 };
    //初始化结构体数组
    for (int i = 0; i < row; i++)
    {
        stu[i] = CursorAlloc();
        CursorSpace[stu[i]].next = 0;
        //printf("%d %d %d\n", CursorSpace[stu[i]].num, CursorSpace[stu[i]].next,stu[i]);

    }
    AdjacencyList(graph, row, col, stu);
    //画图
    int draw[5][5] = { 0 };
    for (int i = 0; i < row; i++)
    {
        Position head = CursorSpace[stu[i]].next;
        while (head != 0)
        {
            draw[i][CursorSpace[head].num] = 1;
            head = CursorSpace[head].next;
        }
    }
    //显示图
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            printf("%d ", draw[i][j]);
        }
        printf("\n");
    }
    for (int i = 0; i < row; i++)
        DeleteCursorList(CursorSpace[stu[i]].next);
    // PrinrfCursorList(head);
    // DeleteCursorList(head);

    return 0;
}
//游标链表实现邻接表
void AdjacencyList(int(*graph)[5], int row, int col, Position* stu)
{
    //邻接表
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (graph[i][j] == 1)
            {
                CreateCursor(stu[i], j);
            }
        }
    }
}
//创建游标链表
Position CreateCursor(Position head, int Element)
{
    Position temp = CursorAlloc();
    CursorSpace[temp].num = Element;
    CursorSpace[temp].next = 0;

    if (CursorSpace[head].next == 0)
    {
        CursorSpace[head].next = temp;
    }
    else
    {
        Position pos = CursorSpace[head].next;
        while (CursorSpace[pos].next != 0)
        {
            pos = CursorSpace[pos].next;
        }
        CursorSpace[pos].next = temp;
    }
    return head;
}
//初始化Cursor数组
void InitCursor()
{
    for (int i = 0; i < SpaceSize; i++)
    {
        CursorSpace[i].next = (i == SpaceSize - 1 ? 0 : i + 1);
    }
}
//malloc函数
static Position CursorAlloc()
{
    Position P;
    P = CursorSpace[0].next;
    CursorSpace[0].next = CursorSpace[P].next;
    return P;
}
//free函数
static void CursorFree(Position P)
{
    CursorSpace[P].next = CursorSpace[0].next;
    CursorSpace[0].next = P;
}
//创建节点
Position CreateCursorNode(Position pos, int Element)
{
    Position temp = CursorAlloc();
    CursorSpace[temp].num = Element;
    CursorSpace[temp].next = 0;

    CursorSpace[pos].next = temp;
    pos = temp;

    return pos;
}
//删除链表
void DeleteCursorList(Position pos)
{
    while (pos != 0)
    {
        Position temp = pos;
        pos = CursorSpace[pos].next;
        CursorFree(temp);
    }
}
void PrinrfCursorList(Position pos)
{
    pos = CursorSpace[pos].next;
    while (pos != 0)
    {
        printf("%d\n", CursorSpace[pos].num);
        pos = CursorSpace[pos].next;
    }
}