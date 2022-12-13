#ifndef _RBTREE_H
#define _RBTREE_H
#include <stdlib.h>

typedef int ElementType;
typedef enum Color {RED, BLACK} Color;
typedef struct RedBlackNode {
    ElementType Element;
    struct RedBlackNode* Left;
    struct RedBlackNode* Right;
    struct RedBlackNode* Parent;
    Color Colors;
}_RedBlackNode, *RedBlackNode;

typedef struct RedBlackTree {
    RedBlackNode Root;
    RedBlackNode NullNode;
}_RedBlackTree, *RedBlackTree;

static void SingleLeftRoate(RedBlackTree T, RedBlackNode X);
static void SingleRightRoate(RedBlackTree T, RedBlackNode Y);
static void RBtree_Insert_Fixup(RedBlackTree T, RedBlackNode X);
void RBtree_Insert(RedBlackTree T, ElementType Item);
void RBtree_Transplant(RedBlackTree T, RedBlackNode U, RedBlackNode V);
void RBtree_Delete_Fixup(RedBlackTree T, RedBlackNode X);
void RBtree_Delete(RedBlackTree T, ElementType Item);
RedBlackTree RBtree_Init();
RedBlackNode RBtree_FindMin(RedBlackTree T, RedBlackNode S);
RedBlackNode RBtree_FindMax(RedBlackTree T, RedBlackNode S);
void RBtree_Print(RedBlackTree T);
static void Inorder(RedBlackTree T, RedBlackNode S);
void RBtree_Free(RedBlackTree T);
static void Free(RedBlackTree T, RedBlackNode S);

#endif