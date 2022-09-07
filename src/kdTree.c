#include "kdTree.h"
#include <stdlib.h>

// Inserts a new node and returns root of modified tree
// The parameter depth is used to decide axis of comparison
// where 0 represents the x-axis and 1 represents the y-axis
kdTree kdTreeInsert(kdTree root, kdTreeDataType point[],unsigned int depth)
{
   // calculate current dimension (cd) of comparison
   unsigned int cd = depth % DIM;

   if(root == NULL)
   {
      kdTree temp = malloc(sizeof(kdTreeNode));

      for(int i = 0; i < DIM; i++)
        temp->data[i] = point[i];

      temp->left = temp->right = NULL;
   }
   else if(point[cd]<root->data[cd])
     root->left = kdTreeInsert(root->left, point,depth+1);
   else
     root->right = kdTreeInsert(root->right, point,depth+1);
   
   return root;
}

bool kdTreeFindSame(kdTreeDataType point1[],kdTreeDataType point2[])
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
bool kdTreeSearch(kdTree root, kdTreeDataType point[],unsigned int depth)
{
   if(root == NULL) return false;
   if(kdTreeFindSame(root->data,point)) return true;

   // calculate the current dimension (cd)
   unsigned int cd = depth % DIM;

   // Compare point with root with respect to cd (Current dimension)
   if(point[cd] < root->data[cd])
     return kdTreeSearch(root->left,point,depth+1);

   return kdTreeSearch(root->right,point,depth+1);
}