/**
 * @file CursorBinarySearchTree.c
 * @author Jelly (wugd827@163.com)
 * @brief Exercise 4.11
 * @version 0.1
 * @date 2022-06-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */

// init tree table example
/*
slot   Element    left    right
0                   1       0
1                   2       0
2                   3       0
3                   4       0
4                   5       0
5                   6       0
6                   7       0
7                   8       0
8                   9       0
9                   0       0
*/
#include <stdio.h>
#include <stdlib.h>

#define SpaceSize 100
#define NONE 0
typedef int ElementType;
typedef int ptrNode;
typedef ptrNode Position;
typedef ptrNode SearchTree;

struct _treeNode {
    ElementType data;
    SearchTree left;
    SearchTree right;
};

struct _treeNode CursorSpace[SpaceSize];
static Position CursorAlloc();
static void CursorFree(Position P);
void InitCursor();
SearchTree MakeEmpty(SearchTree T);
Position Find(SearchTree T, ElementType element);
SearchTree Insert(SearchTree T, ElementType element);
Position Find(SearchTree T, ElementType element);
Position FindMin(SearchTree T);
Position FindMax(SearchTree T);
SearchTree Delete(SearchTree T,ElementType element);
SearchTree Preorder(SearchTree T);

int main(int argc, char **argv)
{
    InitCursor();
    SearchTree T = 0;
    int arr[] = {3,1,4,6,9,2,5,7};
    int len = sizeof(arr) / sizeof(arr[0]);
    for (int i = 0; i<len; i++)
    {
        T = Insert(T, arr[i]);
    }
    printf("%d\n",CursorSpace[Find(T,4)].data);
    printf("%d\n",CursorSpace[FindMin(T)].data);
    printf("%d\n",CursorSpace[FindMax(T)].data);
    Delete(T,5);
    Preorder(T);
    T = MakeEmpty(T);
    printf("%d\n",T);
    return 0;
}

//malloc函数
static Position CursorAlloc()
{
    Position P;
    P = CursorSpace[0].left;
    CursorSpace[0].left = CursorSpace[P].left;
    return P;
}
//free函数
static void CursorFree(Position P)
{
    CursorSpace[P].left = CursorSpace[0].left;
    CursorSpace[0].left = P;
}

//初始化Cursor数组
void InitCursor()
{
    for (int i = 0; i < SpaceSize; i++)
    {
        CursorSpace[i].left = (i == SpaceSize - 1 ? 0 : i + 1);
        CursorSpace[i].right = 0;
    }
}
// init binarySearchTree
SearchTree MakeEmpty(SearchTree T)
{
    if(T!=NONE)
    {
        CursorSpace[T].left = MakeEmpty(CursorSpace[T].left);
        CursorSpace[T].right = MakeEmpty(CursorSpace[T].right);
        CursorFree(T);
    }
    return NONE;
}
// find the element from the binary search tree
Position Find(SearchTree T, ElementType element)
{
    if(T==NONE)
       return NONE;
    else if(element<CursorSpace[T].data)//if the element less than the data,go left
       return Find(CursorSpace[T].left,element);
    else if(element>CursorSpace[T].data)//if the element greater then the data,go right
       return Find(CursorSpace[T].right,element);
    return T;
}
// insert element at the binary search tree
SearchTree Insert(SearchTree T, ElementType element)
{
    if(T==NONE)
    {
        T = CursorAlloc();
        CursorSpace[T].data = element;
        CursorSpace[T].left = CursorSpace[T].right = NONE;
    }
    else if(element<CursorSpace[T].data)//if the element less than the data,go left
        CursorSpace[T].left = Insert(CursorSpace[T].left,element);
    else if(element>CursorSpace[T].data)//if the element greater then the data,go right
        CursorSpace[T].right = Insert(CursorSpace[T].right,element);
    return T;
}
Position FindMin(SearchTree T)
{
    if(T==NONE)
      return NONE;
    else if(CursorSpace[T].left==NONE)
      return T;
    else 
      return FindMin(CursorSpace[T].left);
}
Position FindMax(SearchTree T)
{
    if(T==NONE)
      return NONE;
    else if(CursorSpace[T].right==NONE)
      return T;
    else 
      return FindMax(CursorSpace[T].right);
}
SearchTree Delete(SearchTree T,ElementType element)
{
    Position temp = NONE;
    if(T==NONE)
      return NONE;
    else if(element<CursorSpace[T].data)//go left
      CursorSpace[T].left = Delete(CursorSpace[T].left,element);
    else if(element>CursorSpace[T].data)//go right
      CursorSpace[T].right = Delete(CursorSpace[T].right,element);
    else if(CursorSpace[T].left&&CursorSpace[T].right)//have two children
    {
        temp = FindMin(CursorSpace[T].right);
        CursorSpace[T].data = CursorSpace[temp].data;
        CursorSpace[T].right = Delete(CursorSpace[T].right,CursorSpace[temp].data);
    }
    else //have one or zero children
    {
        temp = T;
        if(CursorSpace[T].left==NONE)
          T = CursorSpace[T].right;
        else if(CursorSpace[T].right==NONE)
          T = CursorSpace[T].left;
        CursorFree(temp);
    }
    return T;
}
// preorder traversal of binary search tree
SearchTree Preorder(SearchTree T)
{
    if(T!=NONE)
       printf("%d ",CursorSpace[T].data);
    else
      return T;
    Preorder(CursorSpace[T].left);
    Preorder(CursorSpace[T].right);
    return T;
}