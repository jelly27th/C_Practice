#ifndef _KDTREE_H
#define _KDTREE_H
#include <stdbool.h>

#define DIM 2
typedef int kdTreeDataType;
typedef struct _kdTreeNode kdTreeNode;
typedef kdTreeNode* kdTree;
typedef kdTreeNode* kdTreePosition;
typedef kdTree* kdTreeAdress;


struct _kdTreeNode {
    kdTreeDataType data[DIM];//store DIM dimensional point
    kdTree left;
    kdTree right;
};

kdTree kdTreeInsert(kdTree root, kdTreeDataType point[],unsigned int depth);
bool kdTreeSearch(kdTree root, kdTreeDataType point[],unsigned int depth);
bool kdTreeFindSame(kdTreeDataType point1[],kdTreeDataType point2[]);

#endif