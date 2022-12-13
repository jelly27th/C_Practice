/**
 * @file RBtree.c
 * @author Jelly (wugd827@163.com)
 * @brief Reference from [红黑树算法和应用(更高级的二叉查找树)](http://data.biancheng.net/view/85.html)
 *        Detailed operation details can be seen [通俗易懂的红黑树图解 (下)](https://www.infoq.cn/article/h8CPxRB2WKgQpBm7Irm1) 
 *        and [通俗易懂的红黑树图解 (上)](https://www.infoq.cn/article/xbzme1oqnkicaywiubrc)
 * @version 0.1
 * @date 2022-12-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "RBtree.h"
#include <stdio.h>

/*
*        |                           |
*        X         left roate        Y
*       / \        ---------->      / \
*      a   Y       <----------     X   c
*         / \       right roate   / \ 
*        b   c                   a   b 
*
*/
static void SingleLeftRoate(RedBlackTree T, RedBlackNode X) {
    RedBlackNode Y = X->Right;

    X->Right = Y->Left;
    // If the right subtree of X is not NullNode, it needs to 
    // reconnect the parent node of the right subtree is X.
    if (X->Right != T->NullNode) {
        X->Right->Parent = X;
    }

    // Sets the parent of Y to be the parent of X
    Y->Parent = X->Parent;

    // Reset the connection between the parent node of Y and X, 
    // divided into two cases:
    // 1. The original X node itself is several root nodes of the whole tree. 
    // At this time, it is only necessary to point the T pointer to Y.
    // 2. Determine whether Y is the left or right child of the parent node 
    // according to the value of the keyword in Y and the value of the keyword of its parent node
    if (Y->Parent == T->NullNode)
        T->Root = Y;
    else if (Y->Element < Y->Parent->Element)
        Y->Parent->Left = Y;
    else
        Y->Parent->Right = Y;
    
    Y->Left = X;
    X->Parent = Y;
}

// The Operation like SingleLeftRoate(). 
static void SingleRightRoate(RedBlackTree T, RedBlackNode Y) {
    RedBlackNode X = Y->Left;

    Y->Left = X->Right;
    
    if (Y->Left != T->NullNode) {
        Y->Left->Parent = Y;
    }

    X->Parent = Y->Parent;

    if (X->Parent == T->NullNode)
        T->Root = X;
    else if (X->Element < X->Parent->Element)
        X->Parent->Left = X;
    else
        X->Parent->Right = X;
    
    X->Right = Y;
    Y->Parent = X;
}

static void RBtree_Insert_Fixup(RedBlackTree T, RedBlackNode X) {
    //First judge that the color of the parent node needs to be adjusted when it is red.
    // when it is black, it can be directly inserted without adjustment.
    RedBlackNode uncle;
    while (X->Parent->Colors == RED) {
        // Determine whether the parent node is the left child or the right child of the grandparent node.
        // First: If the parent node is the right child of the grandparent node.
        if (X->Parent == X->Parent->Parent->Left) {
            uncle = X->Parent->Parent->Right; // Find its uncle node
        
            //Case 1: If the color of the uncle node is red. 
            if (uncle->Colors == RED) {
                X->Parent->Colors = BLACK;
                uncle->Colors = BLACK;
                X->Parent->Parent->Colors = RED;
                X = X->Parent->Parent;
            } else {
                // If the color of the uncle node is black. 
                if (X == X->Parent->Right) {
                    // Case 2: X is right child of the parent node.
                    X = X->Parent;
                    SingleLeftRoate(T, X);
                } else {
                    // Case 3: X is left child of the parent node.
                    X->Parent->Colors = BLACK;
                    X->Parent->Parent->Colors = RED;
                    SingleRightRoate(T, X->Parent->Parent);
                }
            }
        } else {
            // Second : If the parent node is the left child of the grandparent node.
            // This mirrors the three cases above.
            uncle = X->Parent->Parent->Left;

            //Case 1: If the color of the uncle node is red. 
            if (uncle->Colors == RED) {
                X->Parent->Colors = BLACK;
                uncle->Colors = BLACK;
                X->Parent->Parent->Colors = RED;
                X = X->Parent->Parent;
            } else {
                // If the color of the uncle node is black. 
                if (X == X->Parent->Left) {
                    // Case 2: X is left child of the parent node.
                    X = X->Parent;
                    SingleRightRoate(T, X);
                } else {
                    // Case 3: X is right child of the parent node.
                    X->Parent->Colors = BLACK;
                    X->Parent->Parent->Colors = RED;
                    SingleLeftRoate(T, X->Parent->Parent);
                }
            } 
        }
    }
    T->Root->Colors = BLACK;
} 
// The insertion operation is divided into three steps: 
// 1. Use the red-black tree as a binary search tree to find its insertion position.
// 2. Initialize the insertion node and set the color of the new node to red.
// 3. By calling the adjustment function, the two Fork search tree changed to red-black tree.
void RBtree_Insert(RedBlackTree T, ElementType Item) {
    // 1. Find place to insert
    RedBlackNode X, P;
    X = T->Root;
    P = X;
    while (X != T->NullNode) {
        P = X;
        if (Item < X->Element)
            X = X->Left;
        else if (Item > X->Element)
            X = X->Right;
        else {
            printf("%d is exist\n", Item);
            return ;
        }
    }

    // 2. Initialize node, default red.
    X = malloc(sizeof(_RedBlackNode));
    X->Element = Item;
    X->Colors = RED;
    X->Left = X->Right = T->NullNode;
    X->Parent = P;

    // For the newly inserted node, establish a connection with its parent node.
    if (T->Root == T->NullNode) 
        T->Root = X;
    else if (Item < P->Element)
        P->Left = X;
    else 
        P->Right = X;
    
    // 3. Adjusting the Binary Search Tree.
    RBtree_Insert_Fixup(T, X);
}

void RBtree_Transplant(RedBlackTree T, RedBlackNode U, RedBlackNode V) {
    if (U->Parent == T->NullNode)
        T->Root = V;
    else if (U == U->Parent->Left)
        U->Parent->Left = V;
    else 
        U->Parent->Right = V;
    
    V->Parent = U->Parent;
}

void RBtree_Delete_Fixup(RedBlackTree T, RedBlackNode X) {
    RedBlackNode sibling;
    // X is the node to be deleted
    while (X != T->Root && X->Colors == BLACK) {
        // 1. If X is the left child of the parent node.
        if (X == X->Parent->Left) {
            sibling = X->Parent->Right;
            // case 1: sibling nodes are red.
            if (sibling->Colors == RED) {
                sibling->Colors = BLACK;
                sibling->Parent->Colors = RED;
                SingleLeftRoate(T, X->Parent);
                sibling = X->Parent->Right;
            }
            // Case 2: sibling node is black, and both child nodes of the sibling node are black
            if (sibling->Left->Colors == BLACK && sibling->Right->Colors == BLACK) {
                sibling->Colors = RED;
                X = X->Parent;
            }
            // Case 3: sibling node is black, its left child is red, and its right child is black.
            if (sibling->Left->Colors == RED && sibling->Right->Colors == BLACK) {
                sibling->Left->Colors = BLACK;
                sibling->Colors = RED;
                SingleRightRoate(T, sibling);
                sibling = X->Parent->Right;
            }
            // Case 4: The sibling node is black, its right child is red 
            // (the left child doesn't matter what color it is)
            if (sibling->Right->Colors == RED) {
                sibling->Colors = X->Parent->Colors;
                X->Parent->Colors = BLACK;
                sibling->Right->Colors = BLACK;
                SingleLeftRoate(T, X->Parent);
                X = T->Root;
            }
        } else {
            // 2. If X is the right child of the parent node.
            sibling = X->Parent->Right;
            // case 1: sibling nodes are red.
            if (sibling->Colors == RED) {
                sibling->Colors = BLACK;
                sibling->Parent->Colors = RED;
                SingleRightRoate(T, X->Parent);
                sibling = X->Parent->Left;
            }
            // Case 2: sibling node is black, and both child nodes of the sibling node are black
            if (sibling->Left->Colors == BLACK && sibling->Right->Colors == BLACK) {
                sibling->Colors = RED;
                X = X->Parent;
            }
            // Case 3: sibling node is black, its left child is black, and its right child is red.
            if (sibling->Left->Colors == BLACK && sibling->Right->Colors == RED) {
                sibling->Right->Colors = BLACK;
                sibling->Colors = RED;
                SingleLeftRoate(T, sibling);
                sibling = X->Parent->Left;
            }
            // Case 4: The sibling node is black, its left child is red 
            // (the right child doesn't matter what color it is)
            if (sibling->Left->Colors == RED) {
                sibling->Colors = X->Parent->Colors;
                X->Parent->Colors = BLACK;
                sibling->Left->Colors = BLACK;
                SingleRightRoate(T, X->Parent);
                X = T->Root;
            }
        }
    }
    X->Colors = BLACK;
}

void RBtree_Delete(RedBlackTree T, ElementType Item) {
    if (T->Root == T->NullNode) return;

    // Find the node to be deleted
    RedBlackNode toDelete = T->Root;
    RedBlackNode X = T->NullNode;
    // find the node with value Item
    while (toDelete != T->NullNode && toDelete->Element != Item) {
        if (Item < toDelete->Element) 
            toDelete = toDelete->Left;
        else if (Item > toDelete->Element)
            toDelete = toDelete->Right;
    }
    if (toDelete == T->NullNode) {
        printf("%d is not exists\n", Item);
        return ;
    }

    // If there are two children, find the smallest node in the right subtree, 
    // replace it, and delete the node directly
    if (toDelete->Left != T->NullNode && toDelete->Right != T->NullNode) {
        RedBlackNode tmp = RBtree_FindMin(T, toDelete->Right);
        // Here only the value is copied, not the color, 
        // so as not to destroy the nature of the red-black tree
        Item = toDelete->Element = tmp->Element;
        toDelete = tmp;
    }

    // If there is only one child node (only the left child or only the right child), 
    // just use the child node to replace the node position 
    // (this judgment statement is also used if there is no child node).
    if (toDelete->Left == T->NullNode) {
        X = toDelete->Right;
        RBtree_Transplant(T, toDelete, toDelete->Right);
    } else if (toDelete->Right == T->NullNode) {
        X = toDelete->Left;
        RBtree_Transplant(T, toDelete, toDelete->Left);
    }
    
    //Before deleting the node, it is necessary to judge the color of the node: 
    //1. if it is red, delete it directly without destroying the red-black tree. 
    //2. if it is black, it will destroy the fifth property of the red-black tree after deletion, 
    // and the tree needs to be make adjustments.
    if (toDelete->Colors == BLACK)
        RBtree_Delete_Fixup(T, X);
    free(toDelete);
}

RedBlackTree RBtree_Init() {
    RedBlackTree T = malloc(sizeof(_RedBlackTree));
    T->NullNode = malloc(sizeof(_RedBlackNode));
    T->NullNode->Colors = BLACK;
    T->NullNode->Left = T->NullNode->Right = T->NullNode;
    T->NullNode->Parent = NULL;
    T->Root = T->NullNode;
    return T;
}

RedBlackNode RBtree_FindMin(RedBlackTree T, RedBlackNode S) {
    if (S == T->NullNode)
        return T->NullNode;
    while (S->Left != T->NullNode) {
        S = S->Left;
    }

    return S;
}

RedBlackNode RBtree_FindMax(RedBlackTree T, RedBlackNode S) {
    if (S == T->NullNode)
        return T->NullNode;
    while (S->Left != T->NullNode) {
        S = S->Right;
    }

    return S;
}

// Inorder traversal
void RBtree_Print(RedBlackTree T) {
    Inorder(T, T->Root);
}

static void Inorder(RedBlackTree T, RedBlackNode S) {
    if (T->NullNode == S)
        return ;
    
    Inorder(T, S->Left);
    if (S->Colors == RED)
        printf("%dR ", S->Element);
    else
        printf("%dB ", S->Element);
    Inorder(T, S->Right);
}

void RBtree_Free(RedBlackTree T) {
    Free(T, T->Root);
    free(T);
}

static void Free(RedBlackTree T, RedBlackNode S) {
    if (S != T->NullNode) {
        Free(T,S->Left);
        Free(T,S->Right);
        free(S);
    }
}