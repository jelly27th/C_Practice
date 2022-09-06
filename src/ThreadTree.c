#include "ThreadTree.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

// find the most left node in T node
ThreadTree ThreadTreeFindLeftMost(ThreadTree T)
{
    if(T == NULL) return NULL;

    while(T->LeftThread != true) T = T->Left;

    return T;  
}
// Non-recursive inorder traversal prints the thread tree
void ThreadTreeInorder(ThreadTree root)
{
    ThreadTree cur = ThreadTreeFindLeftMost(root);

    while(cur!= NULL)
    {
        printf("%d ",cur->Data);

        if (cur->RightThread==true)
          cur = cur->Right;
        else
          cur = ThreadTreeFindLeftMost(cur->Right);
    }
}

ThreadTree ThreadTreeInsert(ThreadTree root,ThreadTreeDataType Data)
{
  ThreadTree ptr = root;
  ThreadTree par = NULL;

  while(ptr!=NULL)
  {
    if(Data==ptr->Data)
    {
      printf("Data has already been inserted\n");
      return root;
    }

    par = ptr;

    if(Data < ptr->Data && ptr->LeftThread ==false)
     ptr = ptr->Left;
    else if(Data > ptr->Data && ptr->RightThread ==false)
     ptr = ptr->Right;
    else
      break;
  }
  ThreadTree temp = malloc(sizeof(ThreadTreeNode));
  temp->Data = Data;
  temp->LeftThread = temp->RightThread = true;

  if(par == NULL)
  {
    root = temp;
    temp->Left = temp->Right = NULL;
  }
  else if(Data < par->Data)
  {
    temp->Left = par->Left;
    temp->Right = par;
    par->LeftThread = false;
    par->Left = temp;
  }
  else
  {
    temp->Left = par;
    temp->Right = par->Right;
    par->RightThread = false;
    par->Right = temp;
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
  while (ptr!= NULL)
  {
    if(Data == ptr->Data)
    {
      found = true;
      break;
    }
    par = ptr;
    if(Data < ptr->Data&&ptr->LeftThread == false) 
      ptr = ptr->Left;
    else if(Data > ptr->Data && ptr->RightThread == false) 
      ptr = ptr->Right;
    else
      break;
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
   root = NULL;
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
  else child = T->Right;

  if(parent == NULL) root = child;
  // left children
  else if(T == parent->Left) parent->Left = child;
  // right children
  else parent->Right = child;

  // find successor and predecessor
  ThreadTree succ = ThreadTreeFindSucc(T);
  ThreadTree pred = ThreadTreeFindPred(T);

  if(T->LeftThread == false) pred->Right = succ;
  else if(T->RightThread == false) succ->Left = pred;

  free(T);
  return root; 
}

ThreadTree ThreadTreeDeleteTwoChildren(ThreadTree root,ThreadTree parent,ThreadTree T)
{
  // find inorder successor and its parent
  ThreadTree parsucc = T;
  ThreadTree succ = T->Right;

  // find leftmost child of successor
  while(succ->LeftThread == false)
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
  if(T==NULL) return NULL;
  while(T!= NULL) T = T->Left;
  return T;
}
ThreadTree ThreadTreeFindMax(ThreadTree T)
{
  if(T==NULL) return NULL;
  while(T!= NULL) T = T->Right;
  return T;
}
// destory the entire double thread tree 
ThreadTree ThreadTreeDestory(ThreadTree T)
{
  T = ThreadTreeFindLeftMost(T);
  ThreadTree temp = NULL;

  while(T!= NULL)
  {
    temp = T;
    if(T->RightThread==true)
      T = T->Right;
    else
      T = ThreadTreeFindLeftMost(T->Right);

    free(temp);
  }
}