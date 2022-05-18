/**
 * @file Cursor.c
 * @author 吴国栋 (872908391@qq.com)
 * @brief 习题3.14 b(未完成)
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
Position CreateCursorNode(Position pos,int Element);

void InitCursor();

int main(int argc, char **argv)
{
    InitCursor();
    /**          0
               / \ \
              1 --\-2
                  /\ |
                3 ---4
    **/
    // int graph[5][5] = {
    //     {0,1,1,0,1},
    //     {1,0,1,0,0},
    //     {1,1,0,1,0},
    //     {0,0,1,0,1},
    //     {1,0,0,1,0}
    // };
    // int col = sizeof(graph[0]) / sizeof(graph[0][0]);//列
    // int row = sizeof(graph) / sizeof(graph[0]);//行
    int arr[] = {0,1,2,3,4,5};
    Position head = CursorAlloc();
    Position pos = head;
    for (int i = 0; i <6;i++)
    {
        pos = CreateCursorNode(pos,arr[i]);
    }
    PrinrfCursorList(head);
    DeleteCursorList(head);

    return 0;
}
//初始化Cursor数组
void InitCursor()
{
    for (int i = 0; i < SpaceSize; i++)
    {
        CursorSpace[i].next = (i==SpaceSize-1?0:i+1);
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
Position CreateCursorNode(Position pos,int Element)
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
    while(pos != 0)
    {
        Position temp = pos;
        pos = CursorSpace[pos].next;
        CursorFree(temp);
    }
}
void PrinrfCursorList(Position pos)
{
    pos = CursorSpace[pos].next;
    while(pos != 0)
    {
        printf("%d\n",CursorSpace[pos].num);
        pos = CursorSpace[pos].next;
    }
}