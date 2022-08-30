/**
 * @file AvlTree.c
 * @author Jelly (wugd827@163.com)
 * @brief Exercise 4.18 and Exercise 4.19 and Exercise 4.22
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
/*
       K2                K1
     /   \     LL       /  \   
    K1    Z    -->    x1    k2
   /  \              /     / \
  x1    Y           X2    Y   Z
 /
X2
*/
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
/*
       K1                       k2     
      /  \                     /  \
     X    k2      RR          K1   Z1
         /  \     -->        /  \    \
        Y   Z1              X    Y    Z2
             \  
              Z2  
*/
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
/*
      K3                      K3                            K2
     /  \                    /  \                          /  \
    K1   D      RR          K2   D            LL          K1   K3
   /  \         -->        /  \               -->        / \   / \
  A    K2                 K1   C                        A   B C   D
      /  \               /  \                         
     B    C             A    B
*/
static Position DoubleRoateLeft(Position K3)
{
  K3->left = SingleRoateRight(K3->left);
  return SingleRoateLeft(K3); 
}
// roate the type of the RL
/*
        k1                           k1                         k2
       /  \                         /  \                       /  \
      A    K3        LL            A    K2         RR         K1   K3
          /  \       -->               /  \        -->       /  \  / \
         K2   D                       B    K3               A    B C  D   
        / \                               /  \
       B   C                             C    D 
*/
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
    else if(element<T->data)//element less than node data,go left and push it
    {
      Push(S, T);
      T = T->left;
    }
    else if(element>T->data)//more than node data,go right and push it
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

AvlTree AvlDelete(AvlTree T, AvlElementType element)
{
  Position temp = NULL;
  if(T==NULL)//when the point is null
    return NULL;
  else if(element<T->data)//go left
  {
    T->left = AvlDelete(T->left,element);
    // the statment is to deal with a parent node that has only one child node
    T->height = MAX(Height(T->left),Height(T->right))+1;
    // when you delete the node in the left subtree,return the root node
    // There are two situations:
    // 1. it will occur the unbalanced type of RL
    // 2. it will occur the unbalanced type of RR
    if(Height(T->right)-Height(T->left)==2)
    {
      if(Height(T->right->left)>Height(T->right->right))
        T = DoubleRoateRight(T);//RL
      else
        T = SingleRoateRight(T);//RR
    }
  }
  else if(element>T->data)//go right
  {
    T->right = AvlDelete(T->right,element);
    // the statment is to deal with a parent node that has only one child node
    T->height = MAX(Height(T->left),Height(T->right))+1;
    // when you delete the node in the right subtree,return the root node
    // There are two situations:
    // 1. it will occur the unbalanced type of LR
    // 2. it will occur the unbalanced type of LL
    if(Height(T->left)-Height(T->right)==2)
    {
      if(Height(T->left->right)>Height(T->left->left))
        T = DoubleRoateLeft(T);//LR
      else
        T = SingleRoateLeft(T);//LL
    }
  }
  else if(T->left&&T->right)//have two children
  {
    //if the height of left subtree more than the height of right subtree
    //find the maximun of the left subtree and write the data to T Node
    //then delete the maximun of the left subtree
    //otherwise use the opposite method
    if(Height(T->left)>Height(T->right))
    {
      temp = AvlFindMax(T->left);
      T->data = temp->data;
      T->left = AvlDelete(T->left,temp->data);
    }
    else
    {
      temp = AvlFindMin(T->right);
      T->data = temp->data;
      T->right = AvlDelete(T->right,temp->data);
    }
  }
  else//have one or zero children
  {
    temp = T;
    if(T->left==NULL) T = T->right;
    else if(T->right==NULL) T = T->left;
    free(temp);
  }
  //when the point is not NULL,update the height of the node
  if(T!= NULL)
    T->height = MAX(Height(T->left),Height(T->right))+1;
  return T;
}
//Here is another version of the double roation functions,
// it is said to be far more efficient than two single roation functions
// note: I have not tested either of these functions
// because i don't want to rewrite AvlDelete function,although it is not difficult\

// roate the type of the LR
/*
      K3                              K2
     /  \                            /  \
    K1   D      LR                  K1   K3
   /  \         -->                / \   / \
  A    K2                         A   B C   D
      /  \                                       
     B    C          
*/
static Position AnotherDoubleRoateLeft(Position K3)
{
  Position K1,K2;

  K1 = K3->left;
  K2 = K1->right;

  K1->right = K2->left;
  K3->left = K2->right;
  K2->left = K1;
  K2->right = K3;
  
  K1->height = MAX(Height(K1->left),Height(K1->right))+1;
  K3->height = MAX(Height(K3->left),Height(K3->right))+1;
  K2->height = MAX(Height(K2->left),Height(K2->right))+1;

  return K2;
}
// roate the type of the RL
/*
        k1                       k2
       /  \                     /  \
      A    K3        RL        K1   K3
          /  \       -->      /  \  / \
         K2   D              A    B C  D   
        / \                    
       B   C               
*/
static Position AnotherDoubleRoateRight(Position K1)
{
  Position K2,K3;

  K3 = K1->left;
  K2 = K3->left;

  K1->right = K2->left;
  K3->left = K2->right;
  K2->left = K1;
  K2->right = K3;

  K1->height = MAX(Height(K1->left),Height(K1->right))+1;
  K3->height = MAX(Height(K3->left),Height(K3->right))+1;
  K2->height = MAX(Height(K2->left),Height(K2->right))+1;

  return K2;
}

AvlTree MinGenTree(int height, int* lastNode)
{
  AvlTree T;

  if(height>=0)
  {
    T = malloc(sizeof(AvlNode));
    T->left = MinGenTree(height-1,lastNode);
    T->data = ++(*lastNode);
    T->height = 0;
    T->right = MinGenTree(height-2,lastNode);
    // update height
    T->height = MAX(Height(T->left),Height(T->right))+1;
    return T;
  }
  else
    return NULL;
}

AvlTree MinAvlTree(int H)
{
  int lastNodeAssigned = 0;
  return MinGenTree(H,&lastNodeAssigned);
}

AvlTree PerfectGenTree(int height, int* lastNode)
{
  AvlTree T;

  if(height>=0)
  {
    T = malloc(sizeof(AvlNode));
    T->left = PerfectGenTree(height-1,lastNode);
    T->data = ++(*lastNode);
    T->height = 0;
    T->right = PerfectGenTree(height-1,lastNode);
    // update the height
    T->height = MAX(Height(T->left),Height(T->right))+1;
    return T;
  }
  else
    return NULL;
}

AvlTree PerfectAvlTree(int H)
{
  int lastNodeAssigned = 0;
  return PerfectGenTree(H,&lastNodeAssigned);
}

// This is actually an in-order traversal program, theoretically applicable to all kinds of trees
// The main use is to print trees
void AvlPrintTree(AvlTree T)
{
  if(T!= NULL)
  {
    AvlPrintTree(T->left);
    printf("%d ",T->data);
    AvlPrintTree(T->right);
  }
}
// This is actually a post-order traversal procedure, theoretically applicable to all kinds of trees
// The main use is to calculate the height of each node
int AvlHeight(AvlTree T)
{
  if(T == NULL)
    return -1;
  else 
    return 1 + MAX(AvlHeight(T->left),AvlHeight(T->right));
}

void AvlCalcX(AvlTree T, int* LastX)
{
  if(T!= NULL)
  {
    AvlCalcX(T->left,LastX);
    T->x = (++(*LastX));
    AvlCalcX(T->right,LastX);
  }
}
void AvlCalcY(AvlTree T, int TreeHeight)
{
  if(T!= NULL)
  {
    T->y = TreeHeight - T->height;
    AvlCalcY(T->left,TreeHeight);
    AvlCalcY(T->right,TreeHeight);
  }
}
void AvlCalcCoordinates(AvlTree T)
{
  int x = 0;
  AvlCalcX(T, &x);
  AvlCalcY(T,T->height);
}
void AvlDir(AvlTree T)
{
  if(T!= NULL)
  {
    printf("%d  x:%d  y:%d\n",T->data,T->x,T->y);
    AvlDir(T->left);  
    AvlDir(T->right);
  }
}

// 打印二叉树:   type : 0表示根节点，１表示左节点，２表示右节点. level表示层次，用于控制显示的距离
void printTree2(AvlTree n, int type,  int level)
{
	int i;

	if (NULL == n)
		return;

	printTree2(n->right, 2, level+1);
	switch (type)
	{
	case 0:
		printf("%2d\n", n->data);
		break;
	case 1:
		for (i = 0; i < level; i++)	
			printf("\t");
		printf("\\ %2d\n", n->data);
		break;
	case 2:
		for (i = 0; i < level; i++)	
			printf("\t");
		printf("/ %2d\n", n->data);
		break;	
	}
	printTree2(n->left, 1,  level+1);
}