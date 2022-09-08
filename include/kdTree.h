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

static kdTree kdTreeInsertRec(kdTree root, kdTreeDataType point[],unsigned int depth);
kdTree kdTreeInsert(kdTree root, kdTreeDataType point[]);
static bool kdTreeSearchRec(kdTree root, kdTreeDataType point[],unsigned int depth);
static bool kdTreeFindSame(kdTreeDataType point1[],kdTreeDataType point2[]);
bool kdTreeSearch(kdTree root, kdTreeDataType point[]);
static void kdTreePrintRangeRec(kdTree root, kdTreeDataType Low[], kdTreeDataType High[], unsigned int depth);
void kdTreePrintRange(kdTree root, kdTreeDataType Low[], kdTreeDataType High[]);

#endif