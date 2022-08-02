#include "BinaryTree.h"
#include <stdio.h>

int main(int argc, char **argv)
{
  int arr[] = {53,17,19,61,98,75,79,63,46,40};
  BinaryTree T =  NULL;
  int len = sizeof(arr)/ sizeof(arr[0]);
  for (int i = 0; i < len; i++)
  {
    T = BinaryInsert(T,arr[i]);
  }
  printf("the node = %d\nthe leacves = %d\nthe full = %d\n",CountNodes(T),CountLeaves(T),CountFull(T));
  T = BinaryMakeEmpty(T);
  return 0;
}