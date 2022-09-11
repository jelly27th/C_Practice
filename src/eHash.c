/**
 * @file eHash.c
 * @author Jelly (wugd827@163.com)
 * @brief give up coding extending hash(Might try to implement if I remember)
 * @version 0.1
 * @date 2022-09-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "eHash.h"
#include <stdlib.h>

eHash eHashInit(int Tablesize)
{
    eHash H = malloc(sizeof(struct eHash));
    H->depth = Tablesize;
    H->TheCell = malloc(sizeof(Bucket)*H->depth);

    for(int i = 0; i < H->depth; i++)
    {
        H->TheCell[i].depth = 0;
        H->TheCell[i].index = i;
    }

    return H;
}

eHash eHashDestory(eHash H)
{
    free(H->TheCell);
    free(H);
    return NULL;
}