#include "kdTree.h"
#include <stdlib.h>
#include <stdio.h>

// Inserts a new node and returns root of modified tree
// The parameter depth is used to decide axis of comparison
// where 0 represents the x-axis and 1 represents the y-axis
static kdTree kdTreeInsertRec(kdTree root, kdTreeDataType point[],unsigned int depth)
{
   // calculate current dimension (cd) of comparison
   unsigned int cd = depth % DIM;

   if(root == NULL)
   {
      root = malloc(sizeof(kdTreeNode));

      for(int i = 0; i < DIM; i++)
        root->data[i] = point[i];

      root->left = root->right = NULL;
   }
   else if(point[cd]<root->data[cd])
     root->left = kdTreeInsertRec(root->left, point,depth+1);
   else
     root->right = kdTreeInsertRec(root->right, point,depth+1);
   
   return root;
}
// Function to insert a new point with given point in
// KD Tree and return new root. It mainly uses above recursive
// function "kdTreeInsertRec"
kdTree kdTreeInsert(kdTree root, kdTreeDataType point[])
{
  return kdTreeInsertRec(root, point, 0);
}
// A method to determine if two Points are same
// in K Dimensional space
static bool kdTreeFindSame(kdTreeDataType point1[],kdTreeDataType point2[])
{
   for(int i=0;i<DIM;i++)
   {
      if(point1[i] != point2[i])
        return false;
   }
   return true;
}
// Searches a Point represented by "point[]" in the K D tree.
// The parameter depth is used to determine current axis.
// where 0 represents the x-axis and 1 represents the y-axis.
static bool kdTreeSearchRec(kdTree root, kdTreeDataType point[],unsigned int depth)
{
   if(root == NULL) return false;
   if(kdTreeFindSame(root->data,point)) return true;

   // calculate the current dimension (cd)
   unsigned int cd = depth % DIM;

   // Compare point with root with respect to cd (Current dimension)
   if(point[cd] < root->data[cd])
     return kdTreeSearchRec(root->left,point,depth+1);

   return kdTreeSearchRec(root->right,point,depth+1);
}
// Searches a Point in the K D tree. It mainly uses
// kdTreeSearchRec()
bool kdTreeSearch(kdTree root, kdTreeDataType point[])
{
    // Pass current depth as 0
    return kdTreeSearchRec(root, point, 0);
}
// Print a point in the K D tree(default 2 D tree).
// It satisfies the following conditions:
// 1. Low[0] <= point[0] <= High[0]
// 2. Low[0] <= point[1] <= High[1]
static void kdTreePrintRangeRec(kdTree root, kdTreeDataType Low[], kdTreeDataType High[], unsigned int depth)
{
  // calculate the current dimension (cd)
  unsigned int cd = depth % DIM;

  if(root != NULL)
  {
    if(Low[0] <= root->data[0] && root->data[0] <= High[0] &&
       Low[1] <= root->data[1] && root->data[1] <= High[1])
       printf("%d %d\n", root->data[0], root->data[1]);
    
    if(Low[cd] <= root->data[cd])
      kdTreePrintRangeRec(root->left,Low,High,depth+1);
    if(High[cd] >= root->data[cd])
      kdTreePrintRangeRec(root->right,Low,High,depth+1);
  }
}
// Print a Point in the K D tree(default 2 D tree). 
// It mainly uses kdTreePrintRangeRec()
void kdTreePrintRange(kdTree root, kdTreeDataType Low[], kdTreeDataType High[])
{
  kdTreePrintRangeRec(root,Low,High,0);
}