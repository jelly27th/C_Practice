/**
 * @file Btree.c
 * @author Jelly (wugd827@163.com)
 * @brief Referenced from https://cloud.tencent.com/developer/article/1127427
 * @version 0.1
 * @date 2022-09-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "Btree.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/*
* Find the keyword position in the tree rooted at node
* If the node where the keyword is found,return the keyword position
*/
KeyPosition BTreeSearch(BTree T, BtreeKeyType Keywords)
{
    KeyPosition pos = 0;
    /*
    * Traverse the current node, find the appropriate keyword, and return the keyword position if an equal keyword is found
    * If no equal node is found, and the node is a leaf node, an error is reported
    * otherwise recursively search
    */
   while(pos<T->KeyNum && Keywords>T->Keywords[pos]) pos++;

   if(pos<T->KeyNum && Keywords==T->Keywords[pos])
   {
     printf("find  keyword %d in %d\n", Keywords, pos);
     return pos;
   }
   else if (T->IsLeaf== true)
     printf("not found the keywords\n");
    else
    return BTreeSearch(T->Child[pos], Keywords);
}
// Function to traverse all nodes in a subtree rooted with
// this node
void BTreeTraverse(BTree T)
{
    // There are n keys and n+1 children, traverse through n
    // keys and first n children
    for (int i = 0; i < T->KeyNum; i++)
    {
        // If this is not leaf, then before printing keywords[i],
        // traverse the subtree rooted with Child[i].
        if(T->IsLeaf==false) BTreeTraverse(T->Child[i]);
        printf("%d ",T->Keywords[i]);
    }
    // Print the subtree rooted with last child
    if(T->IsLeaf==false) BTreeTraverse(T->Child[T->KeyNum+1]);
}
/*
* Insert keywords for the entire tree
* When the tree has only one keyword and is full, a new node needs to be established as the root node of the tree,
* When the root node of the original tree is used as the child node of the new node, the split operation is performed
* Otherwise, directly perform the non-full node insertion operation
*/
BTree BTreeInsert(BTree T, BtreeKeyType Keywords)
{
    // if B tree is empty
    if(T==NULL)
    {
        T = malloc(sizeof(BTreeNode));
        T->Keywords[0] = Keywords;
        T->KeyNum = 1;
        T->IsLeaf = true;
    }
    else //if B tree is not empty
    {
        // if root is full
        if(T->KeyNum == MAX_T - 1)
        {
            /*
                 ---------------         -----           ------    
              T->|10 20 30 40 50|  ->    |   |<-X   ->   | 30 | <-X
                 ----------------        -----           ------
                                          /               /   \
                                         /               /     \  
                                T->|10 20 30 40 50| T->|10 20| |40 50|                              
            */
            BTree X = malloc(sizeof(BTreeNode));
            X->KeyNum = 0;
            X->IsLeaf = false;
            X->Child[0] = T;
            T = X;

            //Split the old root and move 1 keywords to the new root
            BTreeSplit(T,0);

            // New root has two children now.  Decide which of the
            // two children is going to have new keywords 
            int i = 0;
            if(T->Keywords[0]<Keywords) i++;
            BTreeInsertNotFull(T->Child[i], Keywords);
        }
        else //if root is not full
          BTreeInsertNotFull(T, Keywords);
    }
    return T;
}
/*
* Insert keywords for non-full nodes
*/
void BTreeInsertNotFull(BTree T, BtreeKeyType Keywords)
{
    int i = T->KeyNum - 1;

	if(T->IsLeaf==true)
	{
		/* When the node is a leaf node, find the corresponding position,
         insert the keywords, and modify the number of keywords */
		while(i >=0 && Keywords < T->Keywords[i])
		{
			T->Keywords[i+1] = T->Keywords[i];
			i--;
		}
		T->Keywords[i+1] = T->Keywords[i];
		T->KeyNum++;
	}
	else
	{
		/* When it is not a leaf node, find the corresponding child node to determine whether it is a full node, 
        if yes, then split, if not, recursively insert.
             -----                                    -------    
             |30 |                                    |30 60|
             -----                                    -------
             /   \                                    /  |  \
            /     \                                  /   |   \
        ------- -----------------              ------- ------ -------    
        |10 20| | 40 50 60 70 80|   -->        |10 20||40 50| |70 80|
        ------- -----------------              ------- ------ ------- 
        */
		while(i >=0 && Keywords < T->Keywords[i])
			i--;
		i++;
		if(T->Child[i]->KeyNum == MAX_T - 1)
		{
			BTreeSplit(T, i);
			if(Keywords > T->Keywords[i])
				i++;
		}

		BTreeInsertNotFull(T->Child[i], Keywords);
	}
}
/*
* Split the full node of the child node whose location is N
    ---------------                     ------------------
X-> | 1 50 100 200 |                X-> | 1 50 80 100 200 |  
    ---------------                    ------------------- 
    /  /  \   \    \                   /  /  /   \   \   \      
           \                  --->          /     \
     ----------------                   ------    ---------
Y-> | 55 70 80 85 90 |             Y-> | 55 70 |  | 85 90 | <-Z
    -----------------                  ---------  ---------
    /  /   /  \   \  \                  /   \  \   /   \  \
*/
void BTreeSplit(BTree X, KeyPosition N)
{
    /*Create a new empty node Z and Initialize the empty node Z, 
    copy the information of the child node Y to the new node Z */
    BTree Z = malloc(sizeof(BTreeNode));
    BTree Y = X->Child[N];
    Z->IsLeaf = Y->IsLeaf;
    Z->KeyNum = MIN_T - 1;

    /* Copy the (Min_T-1) keywords after the child node Y to the new node Z, 
    and change the number of keywords  of the child node Y */
    for(int i = 0; i < MIN_T-2; i++)
    {
        Z->Keywords[i] = Y->Keywords[i+MIN_T];
    }
    Y->KeyNum = MIN_T - 1;

    /* If the child node Y is not a leaf node, 
    copy the child of the node Y to the new node Z accordingly */
    if(Y->IsLeaf==false)
    {
        for(int i = 0;i<MIN_T -1; i++)
          Z->Child[i] = Y->Child[i+MIN_T];
    }

    /* Move the keyword corresponding to the parent node X and the position of the child node back one place */
    for(int i = X->KeyNum; i>N;i--)
    {
        X->Keywords[i] = X->Keywords[i-1];
        X->Child[i+1] = X->Child[i];
    }

    /* Add new keywords and child nodes to the parent node X, 
    and modify the number of keywords  */
    X->Child[N+1] = Z;
    X->Keywords[N] = Y->Keywords[MIN_T-1];
    X->KeyNum = X->KeyNum + 1;
}
/*
* In order to verify that the insertion and deletion results are correct, add an output function
* Output all keywords of the subtree with parent as the parent node
* Here all the nodes of the same layer are put into an array for easy output
* The first parameter node_first is used as the starting address of each layer of node array
* n is the number of nodes in this layer
*/
// void BTreeDisplay(BTree T, int N)
// {
//     int i = 0,all = 0;

//     /* Output all keywords of the nodes of this layer, 
//     different nodes are separated by " ", 
//     and each layer is separated by "$$" */
//     for(i = 0; i < N; i++)
//     {
//         for(int j = 0; j < (T+i)->KeyNum; j++)
//           printf("%d ",(T+i)->Keywords[j]);
//         all += (T+i)->KeyNum + 1;
//         printf(" ");
//     }
//     printf("$$\n");

//     if(!T->IsLeaf)
//     {
//         BTree Nodes[all];
//         i = 0;
//         for(int j = 0; j < N; j++)
//         {
//             for(int k = 0; k < (T+i)->KeyNum; k++)
//             {
//                 Nodes[i] = (T+i)->Child[k];
//                 i++;
//             }
//         }
//         BTreeDisplay(Nodes, all);
//     }
// }
// Returns the node with the smallest key of the root node tree,
//  and the position of the key must be 0
BtreePosition BTreeFindMin(BTree T)
{
    if(T->KeyNum < 1)
    {
        printf("FindMin failed\n");
        return NULL;
    }

    if(T->IsLeaf)
      return T;
    else 
      T = BTreeFindMin(T->Child[01]);

    return T;  
}
// Returns the node with the largest key of the root node tree, 
// the position of the key must be the n-1 value of the node
BtreePosition BTreeFindMax(BTree T)
{
    if(T->KeyNum < 1)
    {
        printf("FindMax failed\n");
        return NULL;
    }

    if(T->IsLeaf)
      return T;
    else
      T = BTreeFindMax(T->Child[T->KeyNum - 1]);

    return T;
}
/*
* Delete the keyword whose leaf node position is N
* Directly move the keyword after position N forward by one
*/
void BTreeDeleteLeaf(BTree T, int N)
{
    for(int i=N; i<T->KeyNum-1; i++)
        T->Keywords[i] = T->Keywords[i+1];
    
    T->KeyNum = T->KeyNum - 1;
}
// Delete the keyword at position N of the non-leaf node layer
KeyPosition BtreeDeleteNotLeaf(BTree T, KeyPosition N)
{
    // Get the left and right node pointers of the keywords
    BTree Left = T->Child[N];
    BTree Right = T->Child[N + 1];
    BtreeKeyType temp = 0;

    /*
    * When the number of left child node keywords of the keyword currently at this position is greater than or equal to T,
    * Find the key predecessor of the position (the largest key of the left child node)
    */
   if(Left->KeyNum >= MIN_T)
   {
      BTree tmp = BTreeFindMax(Left);
      temp = T->Keywords[N];
      T->Keywords[N] = tmp->Keywords[tmp->KeyNum-1];
      tmp->Keywords[tmp->KeyNum-1] = temp;
   }
   /*
    * On the contrary, if the right child node meets the conditions, 
    * find the successor (that is, the smallest key of the right child node)
    */
   else if(Right->KeyNum >= MIN_T)
   {
      BTree tmp = BTreeFindMin(Right);
      temp = T->Keywords[N];
      T->Keywords[N] = tmp->Keywords[0];
      tmp->Keywords[0] = temp;
      //Keyword position moved to the next position
      N++;
   }
   /*
    * When the left and right child nodes do not meet the conditions, 
    * merge the two child nodes
    */
   else 
    N = BTreeMerage(T,N);

    return N;
}
/*
* Merge two keywords whose number is T-1 and the parent node is the child node whose parent location is location
* Connect two child nodes with the keyword corresponding to the parent node as the intermediate value
* and return the position of the child node that needs to be dropped
*/
KeyPosition BTreeMerage(BTree Parent,KeyPosition N)
{
    if(N==Parent->KeyNum) N--;

    BTree Left = Parent->Child[N];
    BTree Right = Parent->Child[N+1];

    /* Copy the keyword corresponding to the parent node 
    and all the keywords of the right sibling to the node, 
    and modify the n value of the left child */
    Left->Keywords[Left->KeyNum] = Parent->Keywords[N];
    for(int i = 0; i < Left->KeyNum; i++)
    {
        Left->Keywords[MIN_T+i] = Right->Keywords[i];
        Left->KeyNum++;
    }

    /* If there is a child node, also copy to this node */
    if(Right->IsLeaf==false)
    {
        for(int i = 0; i < Right->KeyNum; i++)
          Left->Child[MIN_T+i] = Right->Child[i];
    }

    Right->KeyNum = 0;
    Left->KeyNum = MAX_T-1;

    /* Change the corresponding keyword and child node position of the parent node */
    for(int i = N; i < Parent->KeyNum-1; i++)
    {
        Parent->Keywords[i] = Parent->Keywords[i+1];
        Parent->Child[i+1] = Parent->Child[i+2];
    }

    Parent->KeyNum--;
    BTree temp = Right;
    Right = NULL;
    free(temp);

    return N;
}
// delete keywords in the node
void BTreeDelete(BTree T, BtreeKeyType Keywords)
{
    int i = 0;

    // find keywords location or descending child node position
    while(i<T->KeyNum&&Keywords>T->Keywords[i]) i++;

    // if keywords is found
    if(i<T->KeyNum&&Keywords==T->Keywords[i])
    {
        // if keywords is in leaf nodes
        if(T->IsLeaf==true)
          BTreeDeleteLeaf(T,i);
        else // if keywords is not in leaf nodes
        {
            i = BtreeDeleteNotLeaf(T,i);
            BTreeDelete(T->Child[i],Keywords);
        }
    }
    else // if keywords is not found
    {
        if(T->IsLeaf==true)//Last keyword not found
          printf("the keywords is not in the tree\n");
        else
        {
            /*
            Traverse down to find the keyword, if it satisfies MIN_T,continue the recursion, 
            otherwise, adjust the number of nodes in the left subtree or the right subtree first, 
            after MIN_T is satisfied, continue the recursion.
            */
            if(T->Child[i]->KeyNum >= MIN_T)
              BTreeDelete(T->Child[i], Keywords);
            else
            {
                if(i>0 && T->Child[i-1]->KeyNum >= MIN_T)
                  BTreeBorrowPrev(T,i);
                else if(i>0 && T->Child[i+1] >=MIN_T)
                  BTreeBorrowNext(T,i);
                else
                  i = BTreeMeraged(T,i); 
                
                BTreeDelete(T,Keywords);
            }
        }
    }
}
/*
delete 11
      -------                        ------
 X-> |1 9 20|                    X->|1 7 20|
      ------                         ------
       /   \           ->             /  \
   ---------  ------              ------- ---------    
Y->|4 5 6 7| |11 12|<-Z        Y->|4 5 6| |9 11 12| <-Z
   ---------  ------               ------ ---------
*/
void BTreeBorrowPrev(BTree X, KeyPosition Position)
{
    BTree Y = X->Child[Position-1];
    BTree Z = X->Child[Position];

    for(int i = Z->KeyNum-1; i >= 0; i--)
      Z->Keywords[i+1] = Z->Keywords[i];
    
    Z->Keywords[0] = X->Keywords[Position];
    X->Keywords[Position] = Y->Keywords[Position-1];

    if(Z->IsLeaf==false)
    {
        for(int i = Z->KeyNum;i>=0;i--)
          Z->Child[i+1] = Z->Child[i];
        Z->Child[0] = X->Child[ X->KeyNum];
    }

    Z->KeyNum++;
    Y->KeyNum--;
}
/*
delete 2
      -----                         -----
 X-> |1 4 9|                    X->|1 5 9|
      ------                        ------
      /   \           ->             /  \
     ---  -------                 -----  ----- 
Y-> |2 3| |5 6 7 8|<-Z        Y->|2 3 4| |6 7 8| <-Z
    ----- ---------              ------- ------- 
*/
void BTreeBorrowNext(BTree X, KeyPosition Position)
{
    BTree Y = X->Child[Position];
    BTree Z = X->Child[Position + 1];

    Y->Keywords[Y->KeyNum] = X->Keywords[Position];
    X->Keywords[Position] = Z->Keywords[0];

    for(int i= 0; i<Z->KeyNum-2; i++)
      Z->Keywords[i] = X->Keywords[i+1];

    if(Z->IsLeaf==false)
    {
        Y->Child[Y->KeyNum+1] = Z->Child[0];
        for(int i= 0; i<Z->KeyNum-1; i++)
          Z->Child[i] = Z->Child[i+1];
    }

    Y->KeyNum++;
    Z->KeyNum--;
}