#ifndef _BINARYTREE_H
#define _BINARYTREE_H


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

#endif