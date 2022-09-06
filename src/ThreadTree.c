#include "ThreadTree.h"
#include <stdbool.h>
#include <stdlib.h>

// find the most left node in T node
ThreadTree ThreadTreeFindLeftMost(ThreadTree T)
{
    if(T == NULL) return NULL;

    while(T->LeftThread != true) T = T->Left;

    return T;  
}
// Non-recursive inorder traversal prints the thread tree
void ThreadTreeInorder(ThreadTree T)
{
    ThreadTree T = ThreadTreeFindLeftMost(T);

    while(T!= NULL)
    {
        printf("%d ",T->Data);

        if (T->RightThread==true)
          T = T->Right;
        else
          T = ThreadTreeFindLeftMost(T->Right);
    }
}

ThreadTree ThreadTreeInsert(ThreadTree root,ThreadTreeDataType Data)
{
  if(root == NULL)
  {
    root = malloc(sizeof(ThreadTreeNode));
    root->Data = Data;
    root->Left = root->Right = root;
    root->LeftThread = root->RightThread = true;
  }
  else
  {
    ThreadTree T = root;
    ThreadTree P = malloc(sizeof(ThreadTreeNode));
    P->Data = Data;
    P->LeftThread = P->RightThread = true;
    while(1)
    {
      if(T->Data > Data && T->LeftThread == true)
      {
        P->Left = T->Left;
        P->Right = T;

        T->Left = P;
        T->LeftThread = false;

        break;
      }
      else
       T = T->Right;
      
      if(T->Data < Data && T->RightThread ==true)
      {
        P->Left = T;
        P->Right = T->Right;

        T->Right = P;
        T->RightThread = false;

        break;
      }
      else
       T = T->Left;
    }
  }
  return root;
}
// find the element at the tree and delete it(replace it with a right subtree minimum)
ThreadTree ThreadTreeDelete(ThreadTree root,ThreadTreeDataType Data)
{
  ThreadTree par = NULL, ptr = root;

  // set true if key is found
  bool found = false;

  // The while loop traverses to find the Data location
  while (ptr->LeftThread && ptr->RightThread)
  {
    if(Data == ptr->Data)
    {
      found = true;
      break;
    }
    par = ptr;
    if(Data < ptr->Data)
    {
      if(ptr->LeftThread == false) ptr = ptr->Left;
      else break;
    }
    else
    {
      if(ptr->RightThread == false) ptr = ptr->Right;
      else break;
    }
  }

  if(!found)
    printf("the data %d is not in the thread tree\n",Data);
  // two children
  else if(ptr->LeftThread==false && ptr->RightThread== false)
    root = ThreadTreeDeleteTwoChildren(root,par,ptr);
  // only left children
  else if(ptr->LeftThread==false)
    root = ThreadTreeDeleteOneChildren(root,par,ptr);
  // only right children
  else if(ptr->RightThread==false)
    root = ThreadTreeDeleteOneChildren(root,par,ptr);
  // no children
  else
    root = ThreadTreeDeleteLeaf(root,par,ptr);

  return root; 
}

ThreadTree ThreadTreeDeleteLeaf(ThreadTree root,ThreadTree parent,ThreadTree T)
{
  if(parent==NULL)
   root == NULL;
  else if(T == parent->Left)
  {
    parent->LeftThread = true;
    parent->Left = T->Left;
  }
  else if(T == parent->Right)
  {
    parent->RightThread = true;
    parent->Right = T->Right;
  }
  free(T);

  return root;
}

ThreadTree ThreadTreeDeleteOneChildren(ThreadTree root,ThreadTree parent,ThreadTree T)
{
  ThreadTree child;

  if(T->LeftThread == false) child = T->Left;
  else if(T->RightThread == false) child = T->Right;

  if(parent == NULL) root = child;
  // left children
  else if(T == parent->Left) parent->Left = child;
  // right children
  else if(T == parent->Right) parent->Right = child;

  // find successor and predecessor
  ThreadTree succ = ThreadTreeFindSucc(T);
  ThreadTree pred = ThreadTreeFindPred(T);

  if(T->LeftThread == false) pred->Right = succ;
  else if(T->RightThread == false) succ->Left = pred;

  free(T);
  return root; 
}

ThreadTree ThreadTreeDeleteOneChildren(ThreadTree root,ThreadTree parent,ThreadTree T)
{
  // find inorder successor and its parent
  ThreadTree parsucc = T;
  ThreadTree succ = T->Right;

  // find leftmost child of successor
  while(succ->Left == false)
  {
    parsucc = succ;
    succ = succ->Left;
  }

  T->Data = succ->Data;

  if(succ->LeftThread&&succ->RightThread)
    root = ThreadTreeDeleteLeaf(root,parsucc,succ);
  else
    root = ThreadTreeDeleteOneChildren(root,parsucc,succ);
  
  return root;
}
// find successor or left leaf node(used in delete)
ThreadTree ThreadTreeFindSucc(ThreadTree T)
{
  // find successor
  if(T->RightThread == true) return T->Right;

  // find left leaf node to delete
  T = T->Right;
  while(T->LeftThread == false) T = T->Left;

  return T;
}
// find predecessor or right leaf node(used in delete)
ThreadTree ThreadTreeFindPred(ThreadTree T)
{
  // find predecessor
  if(T->LeftThread == true) return T->Left;

  // find right leaf node to delete
  T = T->Left;
  while(T->RightThread == false) T = T->Right;

  return T;
}
ThreadTree ThreadTreeFindMin(ThreadTree T)
{
  while(T->LeftThread == false) T = T->Left;

  return T;
}
ThreadTree ThreadTreeFindMax(ThreadTree T)
{
  while(T->RightThread == false) T = T->Right;

  return T;
}