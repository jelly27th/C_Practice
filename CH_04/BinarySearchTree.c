/**
 * @file BinarySearchTree.c
 * @author Jelly (wugd827@163.com)
 * @brief Exercise 4.10
 * @version 0.1
 * @date 2022-06-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int ElementType;
typedef struct _treeNode TreeNode;
typedef  TreeNode* SearchTree;
typedef SearchTree* SearchTreeAddress;
typedef  TreeNode* Position;

struct _treeNode{
    ElementType data;
    SearchTree left;
    SearchTree right;
};
SearchTree MakeEmpty(SearchTree T);
Position Find(SearchTree T, ElementType element);
Position FindMin(SearchTree T);
Position FindMax(SearchTree T);
SearchTreeAddress Insert(SearchTreeAddress T,ElementType element);
SearchTree Delete(SearchTree T,ElementType element);
SearchTree Preorder(SearchTree T);

int main(int argc, char** argv)
{
  int arr[] = {53,17,19,61,98,75,79,63,46,40};
  SearchTree T =  NULL;
  int len = sizeof(arr)/ sizeof(arr[0]);
  for (int i = 0; i < len; i++)
  {
    Insert(&T,arr[i]);
  }
  printf("%d\n",Find(T,61)->data);
  printf("%d\n",FindMin(T)->data);
  printf("%d\n",FindMax(T)->data);
  Delete(T,61);
  Preorder(T);
  T = MakeEmpty(T);
  printf("%p\n",T);
  return 0;
}

// init binarySearchTree and create a empty tree
SearchTree MakeEmpty(SearchTree T)
{
    if(T!= NULL)
    {
        MakeEmpty(T->left);
        MakeEmpty(T->right);
        free(T);
    }
    return NULL;
}
// find element in the tree and return position
Position Find(SearchTree T, ElementType element)
{
    if(T==NULL)//when the point is null
      return NULL;
    else if(element<T->data)//if the element less than the data,go left
      return Find(T->left, element);
    else if(element>T->data)//if the element more than the data,go right
      return Find(T->right, element);
    else//if find the element
      return T;
}
// find the minimum element in the tree and return position
Position FindMin(SearchTree T)
{
    if(T==NULL)//when the point is null
      return NULL;
    else if(T->left==NULL)//if find the minimum element
       return T;
    else //if not find the minimum element,go left
      return FindMin(T->left);
}
// find the maximun element in the tree and return position
Position FindMax(SearchTree T)
{
    if(T==NULL)//when the point is null
      return NULL;
    while(T->right==NULL)
    {
        T = T->right;//if not find the maximun element,go right
    }
    return T;
}
// insert element at the tree 
SearchTreeAddress Insert(SearchTreeAddress T,ElementType element)
{
    if(*T==NULL)//when the point is null
    {
        // create a tree node for the tree
        *T = malloc(sizeof(TreeNode));
        (*T)->data = element;
        (*T)->left = (*T)->right = NULL;
    }
    else if((*T)->data>element)//if the element less than the data,go left insert the element
      return Insert(&(*T)->left,element);
    else if((*T)->data<element)//if the element is greater than the data,go right insert the element
      return Insert(&(*T)->right,element);
    return T;//insert completed successfully
}
// find the element at the tree and delete it
SearchTree Delete(SearchTree T,ElementType element)
{
    Position temp = NULL;
    if(T==NULL)//when the point is null
      return NULL;
    else if(element<T->data)//go left
      T->left =  Delete(T->left, element);
    else if(element>T->data)//go Right
      T->right =  Delete(T->right, element);
    else if(T->right&&T->left)//have two children
    {
        temp = FindMin(T->right);
        T->data = temp->data;
        T->right =  Delete(T->right,temp->data);
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
SearchTree Preorder(SearchTree T)
{
  if(T!= NULL)
    printf("%d ",T->data);
  else 
    return T;
  Preorder(T->left);
  Preorder(T->right);
  return T;
}