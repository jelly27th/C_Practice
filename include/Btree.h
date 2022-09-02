#ifndef _BTREE_H
#define _BTREE_H
#include "stdbool.h"

#define MIN_T 3
#define MAX_T (MIN_T * 2)
typedef int BtreeKeyType;
typedef struct _BTreeNode BTreeNode;
typedef BTreeNode* BTree; 
typedef BTreeNode* BtreePosition; 
typedef BTree* BTreeAdress;

struct _BTreeNode {
    int KeyNum;
    bool IsLeaf; //check if this is a leaf.true is leaf.false is not leaf
    BtreeKeyType Keywords[MAX_T-1]; //store keywords
    BTree Child[MAX_T]; //store child nodes.
};

BTree BTreeCreate(); 
int BTreeSearch(BTree T, BtreeKeyType Keywords);
void BTreeSplit(BTree T, int Position);
void BTreeInsertNotFull(BTree T, BtreeKeyType Keywords);
BTree BTreeInsert(BTree T, BtreeKeyType Keywords);
void BTreeDisplay(BTree T, int N);
BTree BTreeFindMin(BTree T);
BTree BTreeFindMax(BTree T);

#endif