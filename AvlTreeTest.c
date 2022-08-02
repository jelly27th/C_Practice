/**
 * @file AvlTreeTest.c
 * @author Jelly (wugd827@163.com)
 * @brief if you use AvlInsertNoRecursion(), you need to stack.h change "typedef AvlTree StackElementType;"
 * @version 0.1
 * @date 2022-06-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include "AvlTree.h"


int main(int argc, char **argv)
{
  // int arr[] = {2,1,4,5,9,3,6,7};
  AvlTree T = NULL;
  // int len = sizeof(arr) / sizeof(arr[0]);
  // for (int i = 0; i < len; i++)
  // {
  //   T = AvlInsert(T,arr[i]);
  //   // T = AvlInsertNoRecursion(T,arr[i]);
  // }
  // T = AvlDelete(T,7);
  // printf("%d %d\n",AvlFindMin(T)->data,AvlFindMin(T)->height);
  // printf("%d %d\n",AvlFindMax(T)->data,AvlFindMax(T)->height);
  // T = MinAvlTree(3);
  T = PerfectAvlTree(3);
  AvlPreorder(T);
  T = AvlMakeEmpty(T);
  // printf("%p\n",T);
  // system("chcp 65001");

  return 0;
}