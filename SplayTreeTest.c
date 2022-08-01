/**
 * @file SplayTreeTest.c
 * @author Jelly (wugd827@163.com)
 * @brief Exercise 4.27
 * @version 0.1
 * @date 2022-07-31
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "SplayTree.h"
#include <stdio.h>
#include <stdlib.h>
#define LENGTH 32

int main(int argc, char **argv)
{
    SplayTree T = NULL;
    for (int i = LENGTH; i >0 ; i--)
    {
        T =  SplayInsert(T, i);
    }
    SplayPreorder(T);
    T = SplayFind(T, 1);
    printf("\n%d\n", T->data);
    SplayPreorder(T);
    T = SplayMakeEmpty(T);
    return 0;
}