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
/*
* Insert keywords for the entire tree
* When the tree has only one keyword and is full, a new node needs to be established as the root node of the tree,
* When the root node of the original tree is used as the child node of the new node, the split operation is performed
* Otherwise, directly perform the non-full node insertion operation
*/
BTree BTreeInsert(BTree T, BtreeKeyType Keywords)
{

	if(T->KeyNum == MAX_T - 1)
	{
		BTree root = malloc(sizeof(BTreeNode));

		root->IsLeaf = true;
		root->KeyNum = 0;
		root->Child[0] = T;
		btree_split_child(root, 0);
		btree_insert_nonfull(root, Keywords);
        T = root;
	}
	else btree_insert_nonfull(T, Keywords);

    return T;
}
/*
* Insert keywords for non-full nodes
*/
void BTreeInsertNotFull(BTree T, BtreeKeyType Keywords)
{
    int i = T->KeyNum - 1;

	if(T->IsLeaf)
	{
		/* When the node is a leaf node, find the corresponding position, insert the keyword, and modify the node node */
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
		/* When it is not a leaf node, find the corresponding child node to determine whether it is a full node, if yes, then split, if not, recursively insert */
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
* Split the full node of the child node whose location is location in the parent node node
*/
void BTreeSplit(BTree T, int Position)
{
    // Create a new empty node
    BTree NewNode = malloc(sizeof(BTreeNode));
    BTree Child = T->Child[Position];

    /* Initialize the empty node newnode, copy the information of the child node childnode to the new node node */
    NewNode->IsLeaf = Child->IsLeaf;
    NewNode->KeyNum = MIN_T - 1;

    /* Copy the (Min_T-1) keywords after the child node childnode to the new node, and change the n value of the child node */
    for(int i = 0; i < MIN_T-2; i++)
    {
        NewNode->Keywords[i] = Child->Keywords[i+MIN_T];
    }
    Child->KeyNum = MIN_T - 1;

    /* If the child node is not a leaf node, copy the node point of the child node to the new node accordingly */
    if(!Child->IsLeaf)
    {
        for(int i = 0;i<MIN_T -1; i++)
          NewNode->Child[i] = Child->Child[i+MIN_T];
    }

    /* Move the keyword corresponding to the parent node and the position of the child node back one place */
    for(int i = T->KeyNum; i>Position;i--)
    {
        T->Keywords[i] = T->Keywords[i-1];
        T->Child[i+1] = T->Child[i];
    }

    /* Add new keywords and child nodes to the parent node, and modify the n value */
    T->Child[Position+1] = NewNode;
    T->Keywords[Position] = Child->Keywords[MIN_T-1];
    T->KeyNum = T->KeyNum + 1;
}
