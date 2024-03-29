#ifndef _BINARYTREE_H
#define _BINARYTREE_H
#include <stdbool.h>

typedef int ElementType;
typedef struct _treeNode TreeNode;
typedef  TreeNode* BinaryTree;
typedef BinaryTree* BinaryTreeAddress;
typedef  TreeNode* Position;

struct _treeNode{
    ElementType data;
    BinaryTree left;
    BinaryTree right;
};
BinaryTree BinaryMakeEmpty(BinaryTree T);
Position BinaryFind(BinaryTree T, ElementType element);
Position BinaryFindMin(BinaryTree T);
Position BinaryFindMax(BinaryTree T);
BinaryTree BinaryInsert(BinaryTree T,ElementType element);
BinaryTree BinaryDeleteRight(BinaryTree T,ElementType element);
BinaryTree BinaryPreorder(BinaryTree T);
BinaryTree BinaryDeleteLeft(BinaryTree T,ElementType element);
void BinaryAlternateDelete(BinaryTree T, ElementType element);
void BinaryRandomDelete(BinaryTree T, ElementType element);
int CountNodes(BinaryTree T);
int CountLeaves(BinaryTree T);
int CountFull(BinaryTree T);
BinaryTree MakeBinaryRandomTree1(int lower,int upper);
BinaryTree MakeBinaryRandomTree(int N);
void BinaryPrintRange(ElementType Lower,ElementType Upper,BinaryTree T);
bool BinarySimilar(BinaryTree T1,BinaryTree T2);

#endif