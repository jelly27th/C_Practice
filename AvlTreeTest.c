#include <stdio.h>
#include <stdlib.h>
#include "AvlTree.h"


int main(int argc, char **argv)
{
  int arr[] = {2,1,4,5,9,3,6,7};
  AvlTree T = NULL;
  int len = sizeof(arr) / sizeof(arr[0]);
  for (int i = 0; i < len; i++)
  {
    T = AvlInsert(T,arr[i]);
  }
  printf("%d %d\n",AvlFindMin(T)->data,AvlFindMin(T)->height);
  printf("%d %d\n",AvlFindMax(T)->data,AvlFindMax(T)->height);
  AvlPreorder(T);
  T = AvlMakeEmpty(T);
  printf("%p\n",T);
//   system("chcp 65001");
  return 0;
}