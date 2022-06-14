#ifndef _AVLTREE_H
#define _AVLTREE_H

#define MAX(a,b) (a > b ? a : b)
typedef int AvlElementType;
typedef struct _AvlNode AvlNode;
typedef AvlNode* AvlTree;
typedef AvlTree* AvlTreeAdress;
typedef AvlNode* Position;

struct _AvlNode{
    AvlElementType data;
    int height;
    AvlTree left;
    AvlTree right;
};

AvlTree AvlMakeEmpty(AvlTree T);
Position AvlFind(AvlTree T, AvlElementType element);
Position AvlFindMin(AvlTree T);
Position AvlFindMax(AvlTree T);
static int Height(Position P);
static Position SingleRoateLeft(Position K2);
static Position SingleRoateRight(Position K1);
static Position DoubleRoateLeft(Position K3);
static Position DoubleRoateRight(Position K1);
AvlTree AvlInsert(AvlTree T, AvlElementType element);
AvlTree AvlPreorder(AvlTree T);
AvlTree AvlInsertNoRecursion(AvlTree T, AvlElementType element);
AvlTree AvlDelete(AvlTree T, AvlElementType element);
#endif
