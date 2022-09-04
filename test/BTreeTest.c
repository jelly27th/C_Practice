#include "Btree.h"
#include <stdio.h>

int main(int argc, char **argv)
{
    int arr[] = {10,20,30,40,50,60,70,80,90};
    BTree T = NULL;

    for (int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++)
    {
        T = BTreeInsert(T, arr[i]);
    }

    BTreeTraverse(T);
    BTreeDelete(T,20);
    BTreeTraverse(T);
    BTreeDelete(T,10);
    BTreeTraverse(T);

    return 0;
}