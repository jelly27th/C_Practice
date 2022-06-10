/**
 * @file AvlTree.c
 * @author Jelly (wugd827@163.com)
 * @brief Exercise 4.18
 * @version 0.1
 * @date 2022-06-08
 * @Reference link https://www.linuxidc.com/Linux/2017-05/144050.htm
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX(a,b) (a > b ? a : b)
typedef int ElementType;
typedef struct _AvlNode AvlNode;
typedef AvlNode* AvlTree;
typedef AvlTree* AvlTreeAdress;
typedef AvlNode* Position;

struct _AvlNode{
    ElementType data;
    int height;
    AvlTree left;
    AvlTree right;
};
AvlTree MakeEmpty(AvlTree T);
Position Find(AvlTree T, ElementType element);
Position FindMin(AvlTree T);
Position FindMax(AvlTree T);
static int Height(Position P);
static Position SingleRoateLeft(Position K2);
static Position SingleRoateRight(Position K1);
static Position DoubleRoateLeft(Position K3);
static Position DoubleRoateRight(Position K1);
AvlTree Insert(AvlTree T, ElementType element);
AvlTree Preorder(AvlTree T);

int main(int argc, char **argv)
{
  int arr[] = {2,1,4,5,9,3,6,7};
  AvlTree T = NULL;
  int len = sizeof(arr) / sizeof(arr[0]);
  for (int i = 0; i < len; i++)
  {
    T = Insert(T,arr[i]);
  }
  printf("%d %d\n",FindMin(T)->data,FindMin(T)->height);
  printf("%d %d\n",FindMax(T)->data,FindMax(T)->height);
  Preorder(T);
  T = MakeEmpty(T);
  printf("%p\n",T);
  return 0;
}

AvlTree MakeEmpty(AvlTree T)
{
    if(T==NULL) 
      return NULL;
    else{
        MakeEmpty(T->left);
        MakeEmpty(T->right);
        free(T);
    }
    return NULL;
}

Position Find(AvlTree T, ElementType element)
{
    if(T==NULL)
      return NULL;
    else if(element<T->data)
      return Find(T->left,element);
    else if(element>T->data)
      return Find(T->right, element);
    return T;
}

Position FindMin(AvlTree T)
{
    if(T==NULL)
      return NULL;
    else if(T->left==NULL)
      return T;
    else
      return FindMin(T->left);
}

Position FindMax(AvlTree T)
{
    if(T==NULL)
      return NULL;
    else if(T->right==NULL)
      return T;
    else
      return FindMax(T->right);
}
// get the height of the node
static int Height(Position P)
{
    if(P==NULL)
      return -1;
    else
      return P->height;
}
// roate the type of the LL
static Position SingleRoateLeft(Position K2)
{
    Position K1;

    K1 = K2->left;
    K2->left = K1->right;
    K1->right = K2;

    K2->height = MAX(Height(K2->left),Height(K2->right))+1;
    K1->height = MAX(Height(K1->left),K2->height)+1;
    return K1;
}
// roate the type of the RR
static Position SingleRoateRight(Position K1)
{
  Position K2;

  K2 = K1->right;
  K1->right = K2->left;
  K2->left = K1;
  // update node height
  K1->height = MAX(Height(K1->left),Height(K1->right))+1;
  K2->height = MAX(Height(K2->right),K1->height)+1;

  return K2;
}
// roate the type of the LR
static Position DoubleRoateLeft(Position K3)
{
  K3->left = SingleRoateRight(K3->left);
  return SingleRoateLeft(K3); 
}
// roate the type of the RL
static Position DoubleRoateRight(Position K1)
{
  K1->right = SingleRoateLeft(K1->right);
  return SingleRoateRight(K1);
}
// insert element in the AvlTree
AvlTree Insert(AvlTree T, ElementType element)
{
  if(T==NULL)
  {
    T = malloc(sizeof(AvlNode));
    T->height = 0;
    T->data = element;
    T->left = T->right = NULL;
  }
  else if(element<T->data)//include the type of the LL and LR
  {
    T->left = Insert(T->left,element);
    if(Height(T->left)-Height(T->right)==2)
    {
      if(element<T->left->data)
        T = SingleRoateLeft(T);//LL
      else
        T = DoubleRoateLeft(T);//RR
    }
  }
  else if(element>T->data)//include the type of the RR and RL
  {
    T->right = Insert(T->right, element);
    if(Height(T->right)-Height(T->left)==2)
    {
      if(element>T->right->data)
        T = SingleRoateRight(T);//RR
      else
        T = DoubleRoateRight(T);//RL
    }
  }
  //update node height
  T->height = MAX(Height(T->left),Height(T->right))+1;
  return T;
}
// Preorder traversal the AvlTree
AvlTree Preorder(AvlTree T)
{
  if(T==NULL)
    return NULL;
  else
  {
    printf("%d ",T->data);
    Preorder(T->left);
    Preorder(T->right);
  }
  return T;
}
