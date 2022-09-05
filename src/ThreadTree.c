#include "ThreadTree.h"
#include <stdbool.h>
#include <stdlib.h>

// find the most left node in T node
ThreadTree ThreadTreeFindLeftMost(ThreadTree T)
{
    if(T == NULL) return NULL;

    while(T->Left != NULL) T = T->Left;

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