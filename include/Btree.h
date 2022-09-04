#ifndef _BTREE_H
#define _BTREE_H
#include "stdbool.h"

#define MIN_T 3
#define MAX_T (MIN_T * 2)
typedef int KeyPosition; 
typedef int BtreeKeyType;
typedef struct _BTreeNode BTreeNode;
typedef BTreeNode* BTree; 
typedef BTreeNode* BtreePosition; 
typedef BTree* BTreeAdress;

struct _BTreeNode {
    int KeyNum;//record number of the keywords
    bool IsLeaf; //check if this is a leaf.true is leaf.false is not leaf
    BtreeKeyType Keywords[MAX_T-1]; //store keywords
    BTree Child[MAX_T]; //store child nodes.
};

KeyPosition BTreeSearch(BTree T, BtreeKeyType Keywords);
void BTreeTraverse(BTree T);
void BTreeSplit(BTree X, KeyPosition N);
void BTreeInsertNotFull(BTree T, BtreeKeyType Keywords);
BTree BTreeInsert(BTree T, BtreeKeyType Keywords);
BtreePosition BTreeFindMin(BTree T);
BtreePosition BTreeFindMax(BTree T);
void BTreeDeleteLeaf(BTree T, KeyPosition N);
KeyPosition BtreeDeleteNotLeaf(BTree T, KeyPosition N);
KeyPosition BTreeMerage(BTree Parent,KeyPosition N);
void BTreeDelete(BTree T, BtreeKeyType Keywords);
void BTreeBorrowPrev(BTree X, KeyPosition Position);
void BTreeBorrowNext(BTree X, KeyPosition Position);

#endif