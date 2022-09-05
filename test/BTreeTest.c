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
    //BTreeDelete(T,90);
    //BTreeDelete(T, 50);
    BTreeDelete(T, 30);
    BTreeTraverse(T);
    BTreeDestroy(T);

    return 0;
}