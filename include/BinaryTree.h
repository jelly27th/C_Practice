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
BinaryTree MakeEmpty(BinaryTree T);
Position Find(BinaryTree T, ElementType element);
Position FindMin(BinaryTree T);
Position FindMax(BinaryTree T);
BinaryTree Insert(BinaryTree T,ElementType element);
BinaryTree DeleteRight(BinaryTree T,ElementType element);
BinaryTree Preorder(BinaryTree T);
BinaryTree DeleteLeft(BinaryTree T,ElementType element);
void AlternateDelete(BinaryTree T, ElementType element);
void RandomDelete(BinaryTree T, ElementType element);
int CountNodes(BinaryTree T);
int CountLeaves(BinaryTree T);
int CountFull(BinaryTree T);

#endif