#ifndef _AVLTREE_H
#define _AVLTREE_H

#define MAX(a,b) (a > b ? a : b)
typedef int ElementType;
typedef struct _AvlNode AvlNode;
typedef AvlNode* AvlTree;
typedef AvlTree* AvlTreeAdress;
typedef AvlNode* Position;

struct _AvlNode{
    ElementType data;
    int height;
    AvlTree left;
    AvlTree right;
};

AvlTree AvlMakeEmpty(AvlTree T);
Position AvlFind(AvlTree T, ElementType element);
Position AvlFindMin(AvlTree T);
Position AvlFindMax(AvlTree T);
static int Height(Position P);
static Position SingleRoateLeft(Position K2);
static Position SingleRoateRight(Position K1);
static Position DoubleRoateLeft(Position K3);
static Position DoubleRoateRight(Position K1);
AvlTree AvlInsert(AvlTree T, ElementType element);
AvlTree AvlPreorder(AvlTree T);
#endif
