/**
 * @file BinaryTree.c
 * @author Jelly (wugd827@163.com)
 * @brief 
 * @version 0.1
 * @date 2022-08-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "BinaryTree.h"
#include "Rand.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


// init binarySearchTree and create a empty tree
BinaryTree BinaryMakeEmpty(BinaryTree T)
{
    if(T!= NULL)
    {
        BinaryMakeEmpty(T->left);
        BinaryMakeEmpty(T->right);
        free(T);
    }
    return NULL;
}
// find element in the tree and return position
Position BinaryFind(BinaryTree T, ElementType element)
{
    if(T==NULL)//when the point is null
      return NULL;
    else if(element<T->data)//if the element less than the data,go left
      return BinaryFind(T->left, element);
    else if(element>T->data)//if the element more than the data,go right
      return BinaryFind(T->right, element);
    else//if find the element
      return T;
}
// find the minimum element in the tree and return position
Position BinaryFindMin(BinaryTree T)
{
    if(T==NULL)//when the point is null
      return NULL;
    else if(T->left==NULL)//if find the minimum element
       return T;
    else //if not find the minimum element,go left
      return BinaryFindMin(T->left);
}
// find the maximun element in the tree and return position
Position BinaryFindMax(BinaryTree T)
{
    if(T==NULL)//when the point is null
      return NULL;
    while(T->right!=NULL)
    {
        T = T->right;//if not find the maximun element,go right
    }
    return T;
}
// insert element at the tree 
BinaryTree BinaryInsert(BinaryTree T,ElementType element)
{
    if(T==NULL)//when the point is null
    {
        // create a tree node for the tree
        T = malloc(sizeof(TreeNode));
        (T)->data = element;
        (T)->left = (T)->right = NULL;
    }
    else if((T)->data>element)//if the element less than the data,go left insert the element
      (T)->left = BinaryInsert((T)->left,element);
    else if((T)->data<element)//if the element is greater than the data,go right insert the element
      (T)->right = BinaryInsert((T)->right,element);
    return T;//insert completed successfully
}
// find the element at the tree and delete it(replace it with a right subtree minimum)
BinaryTree BinaryDeleteRight(BinaryTree T,ElementType element)
{
    Position temp = NULL;
    if(T==NULL)//when the point is null
      return NULL;
    else if(element<T->data)//go left
      T->left =  BinaryDeleteRight(T->left, element);
    else if(element>T->data)//go Right
      T->right =  BinaryDeleteRight(T->right, element);
    else if(T->right&&T->left)//have two children
    {
        temp = BinaryFindMin(T->right);
        T->data = temp->data;
        T->right =  BinaryDeleteRight(T->right,temp->data);
    }
    else //have one or zero children
    {
        temp = T;
        if(T->left==NULL) T = T->right;
        else if(T->right==NULL) T = T->left;
        free(temp);
    }
    return T;
}
// Preorder traversal of binary search tree
BinaryTree BinaryPreorder(BinaryTree T)
{
  if(T!= NULL)
    printf("%d ",T->data);
  else 
    return T;
  BinaryPreorder(T->left);
  BinaryPreorder(T->right);
  return T;
}
// find the element at the tree and delete it(replace it with a left subtree maximun)
BinaryTree BinaryDeleteLeft(BinaryTree T,ElementType element)
{
  Position temp =  NULL;
  if(T==NULL)
    return NULL;
  else if(element<T->data)
    T->left = BinaryDeleteLeft(T->left, element);
  else if(element>T->data)
    T->right = BinaryDeleteLeft(T->right, element);
  else if(T->left&&T->right)//have two children
  {
    temp = BinaryFindMax(T->left);
    T->data = temp->data;
    T->left = BinaryDeleteLeft(T->left, temp->data);
  }
  else //have one or zero children
  {
    temp = T;
    if(T->left==NULL) T = T->right;
    else if(T->right==NULL) T = T->left;
    free(temp);
  }
  return T;
}
// alternately use DeleteLeft() and DeleteRight() to delete element
void BinaryAlternateDelete(BinaryTree T, ElementType element)
{
  static bool flag = true;
  if(flag) BinaryDeleteLeft(T, element);
  else BinaryDeleteRight(T, element);
  flag = !flag;
}

// random use DeleteLeft() and DeleteRight() to delete element
void BinaryRandomDelete(BinaryTree T, ElementType element)
{
  static bool flag = true;
  flag = Rand(2);
  printf("%d\n",flag);
  if(flag==true) BinaryDeleteLeft(T, element);
  else BinaryDeleteRight(T, element);
}
//Calculate the number of nodes
int CountNodes(BinaryTree T)
{
  if(T==NULL) return 0;

  return 1 + CountNodes(T->left) + CountNodes(T->right);
}
//Calculate the number of leaf nodes
int CountLeaves(BinaryTree T)
{
  if(T==NULL)
    return 0;
  else if(T->left==NULL&&T->right==NULL)
    return 1;
  
  return CountLeaves(T->left) + CountLeaves(T->right);
}
//Calculate the number of full nodes 
int CountFull(BinaryTree T)
{
  if(T==NULL) 
    return 0;

  return (T->left!=NULL&&T->right!=NULL)+
           CountFull(T->left) + CountFull(T->right); 
}

BinaryTree MakeBinaryRandomTree1(int lower,int upper)
{
  BinaryTree T;
  int RandomValue;

  T = NULL;
  if(lower<=upper)
  {
    T = malloc(sizeof(TreeNode));      
    if(T!= NULL)
    {
      T->data = RandomValue = RandInt(lower, upper);
      printf("RandomValue = %d\n", RandomValue);
      T->left =  MakeBinaryRandomTree1(lower, RandomValue-1);
      T->right = MakeBinaryRandomTree1(RandomValue+1, upper);
    }
    // else
    //   FatalError("Out of space!");
  }
  return T;
}

BinaryTree MakeBinaryRandomTree(int N)
{
  return MakeBinaryRandomTree1(1, N);
}

