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
 * @brief find the element and make it the root node.
          note: zig-zag(之字形) zig-zig(一字型)
          for detail , you can see Splay().
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
  return Splay(T,element);
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
/*
                y                                     x
               / \     Zig (Right Rotation)          /  \
              x   T3   – - – - – - – - - ->         T1   y 
             / \       < - - - - - - - - -              / \
            T1  T2     Zag (Left Rotation)            T2   T3
*/
static Position LeftRoate(Position x)
{
  Position y = x->right;

  x->right = y->left;
  y->left = x;

  return y;
}
static Position RightRoate(Position y)
{
  Position x = y->left;

  y->left = x->right;
  x->right = y;

  return x;
}
/**
 * @brief There are three types of situations
 *        1) node is root or node is not exists
 *        2) node is child of root  
 *              y                                     x
               / \     Zig (Right Rotation)          /  \
              x   T3   – - – - – - – - - ->         T1   y 
             / \       < - - - - - - - - -              / \
            T1  T2     Zag (Left Rotation)            T2   T3
          3) node has both parent and child , This pack of four cases
          Zig-Zig (Left Left Case):
       G                        P                           X       
      / \                     /   \                        / \      
     P  T4   rightRotate(G)  X     G     rightRotate(P)  T1   P     
    / \      ============>  / \   / \    ============>       / \    
   X  T3                   T1 T2 T3 T4                      T2  G
  / \                                                          / \ 
 T1 T2                                                        T3  T4 

Zag-Zag (Right Right Case):
  G                          P                           X       
 /  \                      /   \                        / \      
T1   P     leftRotate(G)  G     X     leftRotate(P)    P   T4
    / \    ============> / \   / \    ============>   / \   
   T2   X               T1 T2 T3 T4                  G   T3
       / \                                          / \ 
      T3 T4                                        T1  T2
Zag-Zig (Left Right Case):
       G                        G                            X       
      / \                     /   \                        /   \      
     P   T4  leftRotate(P)   X     T4    rightRotate(G)   P     G     
   /  \      ============>  / \          ============>   / \   /  \    
  T1   X                   P  T3                       T1  T2 T3  T4 
      / \                 / \                                       
    T2  T3              T1   T2                                     

Zig-Zag (Right Left Case):
  G                          G                           X       
 /  \                      /  \                        /   \      
T1   P    rightRotate(P)  T1   X     leftRotate(G)    G     P
    / \   =============>      / \    ============>   / \   / \   
   X  T4                    T2   P                 T1  T2 T3  T4
  / \                           / \                
 T2  T3                        T3  T4        
 * @see the code is adopted https://www.geeksforgeeks.org/splay-tree-set-1-insert/
 * @param T 
 * @param element 
 * @return Position 
 * @file SplayTree.c
 * @version 0.1
 * @author Jelly (wugd827@163.com)
 * @date 2022-08-01
 * @copyright Copyright (c) 2022
 */
Position Splay(SplayTree T,SplayElementType element)
{
  //1) root is null or the node is present in root
  if(T==NULL||T->data==element) return T;
  
  //node in left subtree
  if(T->data>element)
  {
    // node is not in tree, we are done
    if(T->left==NULL) return T;

    // 2)zig-zig(left left) 
    if(T->left->data>element)
    {
      T->left->left = Splay(T->left->left,element);

      //Do first rotation for root, second rotation is done after else
      T = RightRoate(T);
    }
    // 3)zig-zag(left right)
    else if(T->left->data<element) 
    {
      T->left->right = Splay(T->left->right,element);

      // Do first rotation for root->left
      if(T->left->right!= NULL)
        T->left = LeftRoate(T->left);
    }

    // Do second rotation for root
    return (T->left==NULL) ? T: RightRoate(T);
  }
  else // node in the right subtree
  {
    // node is not in tree, we are done
    if(T->right==NULL) return T;

    //4)zag-zig(right left) 
    if(T->right->data>element)
    {
      T->right->left =  Splay(T->right->left, element);

      // Do first rotation for root->right
      if(T->right->left!=NULL)
        T->right = RightRoate(T->right);
    }
    //5)zag-zag(right right)
    else if(T->right->data<element)
    {
      T->right->right = Splay(T->right->right, element);

      //Do first rotation for root, second rotation is done after else
      T = LeftRoate(T);
    }
    return (T->right==NULL) ? T : LeftRoate(T);
  }
}