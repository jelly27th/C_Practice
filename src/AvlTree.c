/**
 * @file AvlTree.c
 * @author Jelly (wugd827@163.com)
 * @brief Exercise 4.18 and Exercise 4.19
 * @version 0.1
 * @date 2022-06-11
 * @Reference link https://www.linuxidc.com/Linux/2017-05/144050.htm
 * @copyright Copyright (c) 2022
 * 
 */
#include "AvlTree.h"
#include "Stack.h"
#include<stdio.h>
#include<stdlib.h>

AvlTree AvlMakeEmpty(AvlTree T)
{
    if(T==NULL) 
      return NULL;
    else{
        AvlMakeEmpty(T->left);
        AvlMakeEmpty(T->right);
        free(T);
    }
    return NULL;
}

Position AvlFind(AvlTree T, AvlElementType element)
{
    if(T==NULL)
      return NULL;
    else if(element<T->data)
      return AvlFind(T->left,element);
    else if(element>T->data)
      return AvlFind(T->right, element);
    return T;
}

Position AvlFindMin(AvlTree T)
{
    if(T==NULL)
      return NULL;
    else if(T->left==NULL)
      return T;
    else
      return AvlFindMin(T->left);
}

Position AvlFindMax(AvlTree T)
{
    if(T==NULL)
      return NULL;
    else if(T->right==NULL)
      return T;
    else
      return AvlFindMax(T->right);
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
AvlTree AvlInsert(AvlTree T, AvlElementType element)
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
    T->left = AvlInsert(T->left,element);
    if(Height(T->left)-Height(T->right)==2)
    {
      if(element<T->left->data)
        T = SingleRoateLeft(T);//LL
      else
        T = DoubleRoateLeft(T);//LR
    }
  }
  else if(element>T->data)//include the type of the RR and RL
  {
    T->right = AvlInsert(T->right, element);
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
AvlTree AvlPreorder(AvlTree T)
{
  if(T==NULL)
    return NULL;
  else
  {
    printf("%d ",T->data);
    AvlPreorder(T->left);
    AvlPreorder(T->right);
  }
  return T;
}
// Insert element in the AvlTree with no recursion
AvlTree AvlInsertNoRecursion(AvlTree T, AvlElementType element)
{
  Stack S = CreatStack(10);
  while(true)
  {
    // find the suitable position with the element
    // need a stack to record the path to the element
    if(T==NULL)
    {
      T = malloc(sizeof(AvlNode));
      T->height = 0;
      T->data = element;
      T->left = T->right = NULL;
      Push(S, T);
      break;
    }
    else if(element<T->data)//element less than node data,go left
    {
      Push(S, T);
      T = T->left;
    }
    else if(element>T->data)//more than node data,go right
    {
      Push(S, T);
      T = T->right;
    }
  }
  AvlTree Parent = NULL;
  while(!IsEmpty(S))
  {
    Parent = TopAndPop(S);
    if(T->data<Parent->data)
    {
      Parent->left = T;//element link to parent
      if(Height(Parent->left)-Height(Parent->right)==2)
      {
        if(element<Parent->left->data)
          Parent = SingleRoateLeft(Parent);//LL
        else
          Parent = DoubleRoateLeft(Parent);//LR
      }
    }
    else if(T->data>Parent->data)
    {
      Parent->right = T;//element link to parent
      if(Height(Parent->right)-Height(Parent->left)==2)
      {
        if(element>Parent->right->data)
          Parent = SingleRoateRight(Parent);//RR
        else
          Parent = DoubleRoateRight(Parent);//RL
      }
    }
    T = Parent;
    // update the parent height
    T->height = MAX(Height(T->left),Height(T->right))+1;
  }
  //update the parent height when you not use to roate
  //In fact,I did extra work,because Parent node height is repeatly calculated
  T->height = MAX(Height(T->left),Height(T->right))+1;
  return T;
} 