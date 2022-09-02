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
#include "stdbool.h"

/*
* generate an empty tree
* the keywords is zero and the keywords is leaf node
*/
BTree BTreeCreate()
{
    BTree T = malloc(sizeof(BTreeNode));
    T->KeyNum = 0;
    T->IsLeaf = true;

    return T;
}
/*
* Find the keyword position in the tree rooted at node
* If the node where the keyword is found,return the keyword position
*/
int BTreeSearch(BTree T, BtreeKeyType Keywords)
{
    int pos = 0;
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
			btree_split_child(T, i);
			if(Keywords > T->Keywords[i])
				i++;
		}

		btree_insert_nonfull(T->Child[i], Keywords);
	}
}
/*
* Split the full node of the child node whose location is position
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
void BTreeSplit(BTree X, int Position)
{
    /*Create a new empty node Z and Initialize the empty node Z, 
    copy the information of the child node Y to the new node Z */
    BTree Z = malloc(sizeof(BTreeNode));
    BTree Y = X->Child[Position];
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
    for(int i = X->KeyNum; i>Position;i--)
    {
        X->Keywords[i] = X->Keywords[i-1];
        X->Child[i+1] = X->Child[i];
    }

    /* Add new keywords and child nodes to the parent node X, 
    and modify the number of keywords  */
    X->Child[Position+1] = Z;
    X->Keywords[Position] = Y->Keywords[MIN_T-1];
    X->KeyNum = X->KeyNum + 1;
}
/*
* In order to verify that the insertion and deletion results are correct, add an output function
* Output all keywords of the subtree with parent as the parent node
* Here all the nodes of the same layer are put into an array for easy output
* The first parameter node_first is used as the starting address of each layer of node array
* n is the number of nodes in this layer
*/
void BTreeDisplay(BTree T, int N)
{
    int i = 0,all = 0;

    /* Output all keywords of the nodes of this layer, 
    different nodes are separated by " ", 
    and each layer is separated by "$$" */
    for(i = 0; i < N; i++)
    {
        for(int j = 0; j < (T+i)->KeyNum; j++)
          printf("%d ",(T+i)->Keywords[j]);
        all += (T+i)->KeyNum + 1;
        printf(" ");
    }
    printf("$$\n");

    if(!T->IsLeaf)
    {
        BTree Nodes[all];
        i = 0;
        for(int j = 0; j < N; j++)
        {
            for(int k = 0; k < (T+i)->KeyNum; k++)
            {
                Nodes[i] = (T+i)->Child[k];
                i++;
            }
        }
        BTreeDisplay(Nodes, all);
    }
}
// Returns the node with the smallest key of the root node tree,
//  and the position of the key must be 0
BTree BTreeFindMin(BTree T)
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
BTree BTreeFindMax(BTree T)
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