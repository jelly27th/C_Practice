/**
 * @file SplayTree.c
 * @author Jelly (wugd827@163.com)
 * @brief 
 * @version 0.1
 * @date 2022-07-31
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "SplayTree.h"
#include <stdio.h>
#include <stdlib.h>

SplayTree SplayMakeEmpty(SplayTree T)
{
    if(T==NULL) 
      return NULL;
    else{
        SplayMakeEmpty(T->left);
        SplayMakeEmpty(T->right);
        free(T);
    }
    return NULL;
}
/**
 * @brief find the element and make it the root node
          note: zig-zag(之字形) zig-zig(一字型)
          there are four cases:
          1) the type of left zig-zag ,you can see ZigZagLeftRoate()
          2) the type of right zig-zag ,you can see ZigZagRightRoate()
          3) the type of right zig-zig ,you can see ZigZagLeftRoate()
          4) the type of left zig-zig ,you can see ZigZagRightRoate()
 * 
 * @param T 
 * @param element 
 * @return Position 
 * @file SplayTree.c
 * @version 0.1
 * @author Jelly (wugd827@163.com)
 * @date 2022-07-31
 * @copyright Copyright (c) 2022
 */
Position SplayFind(SplayTree T, SplayElementType element)
{
    if(T==NULL)
      return NULL;
    else if(element<T->data)
    {
      T->left = SplayFind(T->left,element);
      if(T->left->data!=element)
      {
        if(element<T->left->data)
           T = ZigZigLeftRoate(T);
        else
           T = ZigZagLeftRoate(T);
      }
    } 
    else if(element>T->data)
    {
      T->right = SplayFind(T->right, element);
      if(T->right->data!=element)
      {
        if(element>T->right->data)
           T = ZigZigRightRoate(T);
        else
           T = ZigZagRightRoate(T);
      }
    }
    return T;
}
Position SplayFindMin(SplayTree T)
{
    if(T==NULL)
      return NULL;
    else if(T->left==NULL)
      return T;
    else
      return SplayFindMin(T->left);
}
Position SplayFindMax(SplayTree T)
{
    if(T==NULL)
      return NULL;
    else if(T->right==NULL)
      return T;
    else
      return SplayFindMax(T->right);
}
/**
 * @brief roate the type of left zig-zag
 *a example
            G                       X
           / \                     / \ 
          P   D     LR            P   G 
         / \        -->          / \ / \ 
        A   x                   A  B C  D 
           / \
          B   C
 * 
 * @param G 
 * @return Position 
 * @file SplayTree.c
 * @version 0.1
 * @author Jelly (wugd827@163.com)
 * @date 2022-07-31
 * @copyright Copyright (c) 2022
 */
static Position ZigZagLeftRoate(Position G)
{
    Position P,X;

    P = G->left;
    X = P->left;

    P->right =  X->left;
    G->left = X->right;
    X->left = P;
    X->right = G;

    return X;
}
//roate the type of left zig-zig
/*
           G                       X
          / \                     / \ 
         P   D                   A   P
        / \         -->             / \ 
       X   C                       B   G
      / \                             / \ 
     A   B                           C   D  
*/
static Position ZigZigLeftRoate(Position G)
{
    Position P,X;

    P = G->left;
    X = P->left;

    G->left = P->right;
    P->right = G;
    P->left = X->right;
    X->right = P;

    return X;
}
//roate the type of right zig-zag
/*
        G                        X
       /  \                     /  \
      D    P        RL         G     P
          /  \       -->      /  \  / \
         X    A              D    B C  A   
        / \                    
       B   C               
*/
static Position ZigZagRightRoate(Position G)
{
  Position P,X;

  P = G->right;
  X = P->left;

  G->right = X->left;
  P->left = X->right;
  X->left = G;
  X->right = P;

  return X;
}
//roate the type of right zig-zig
//roate the type of left zig-zig
/*
           G                       X
          / \                     / \ 
         P   D                   A   P
        / \         <--             / \ 
       X   C                       B   G
      / \                             / \ 
     A   B                           C   D  
*/
static Position ZigZigRightRoate(Position X)
{
  Position P,G;

  P = X->right;
  G = X->left;

  X->right = P->left;
  P->left = X;
  P->right = G->left;
  G->left = P;

  return G;
}
// This function is no different from the ordinary binary search tree search function.
SplayTree SplayInsert(SplayTree T, SplayElementType element)
{
    if(T==NULL)//when the point is null
    {
        // create a tree node for the tree
        T = malloc(sizeof(SplayNode));
        (T)->data = element;
        (T)->left = (T)->right = NULL;
    }
    else if((T)->data>element)//if the element less than the data,go left insert the element
      (T)->left = SplayInsert((T)->left,element);
    else if((T)->data<element)//if the element is greater than the data,go right insert the element
      (T)->right = SplayInsert((T)->right,element);
    return T;//insert completed successfully
}
SplayTree SplayPreorder(SplayTree T)
{
    if(T==NULL)
    return NULL;
    else
    {
        printf("%d ",T->data);
        SplayPreorder(T->left);
        SplayPreorder(T->right);
    }
    return T;
}
// find the element at the tree and delete it(replace it with a right subtree minimum)
/*
for example, if you delete the element 2(have two children)
           6                           6
          / \                         / \ 
         2   8                       3   8 
        / \           delete        / \
       1   5          -->          1   5
          /                           / 
         3                           4 
          \
           4
or delete the element 4(have one children)
           6                           6
          / \                         / \ 
         2   8                       2   8 
        / \           delete        / \
       1   4          -->          1   3
          /                             
         3    
or delete the element 4(have zero children)    
           6                           6
          / \                         / \ 
         2   8                       2   8 
        / \           delete        / 
       1   4          -->          1                        
*/
SplayTree SplayDelete(SplayTree T, SplayElementType element)
{
    Position temp = NULL;
    if(T==NULL)//when the point is null
      return NULL;
    else if(element<T->data)//go left
      T->left =  SplayDelete(T->left, element);
    else if(element>T->data)//go Right
      T->right =  SplayDelete(T->right, element);
    else if(T->right&&T->left)//have two children
    {
        temp = SplayFindMin(T->right);
        T->data = temp->data;
        T->right =  SplayDelete(T->right,temp->data);
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