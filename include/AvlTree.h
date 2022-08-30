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

    int x;
    int y;
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
AvlTree AvlInsertNoRecursion(AvlTree T, AvlElementType element);
AvlTree AvlDelete(AvlTree T, AvlElementType element);
AvlTree MinGenTree(int height, int* lastNode);
AvlTree MinAvlTree(int H);
AvlTree PerfectGenTree(int height, int* lastNode);
AvlTree PerfectAvlTree(int H);
AvlTree AvlPreorder(AvlTree T);

void AvlCalcX(AvlTree T, int* LastX);
void AvlCalcY(AvlTree T, int TreeHeight);
void AvlCalcCoordinates(AvlTree T);
void AvlDir(AvlTree T);



void AvlPrintTree(AvlTree T);
int AvlHeight(AvlTree T);
void printTree2(AvlTree n, int type,  int level);


#endif
