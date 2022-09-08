#include <stdio.h>
#include <stdlib.h>
#include "kdTree.h"

int main(int argc, char **argv)
{
    int arr[][DIM] = {
        {3,6},
        {17,15},
        {13,15},
        {6,12},
        {9,12},
        {2,7},
        {10,19}
    };
    kdTree root = NULL;

    for (int i = 0; i <sizeof(arr)/sizeof(arr[0]); i++)
    {
        root = kdTreeInsert(root, arr[i]);
    }

    int point1[] = {10,19};
    printf("%d\n",kdTreeSearch(root, point1));

    int point2[] = {12,19};
    printf("%d\n",kdTreeSearch(root, point2));

    int low[] = {2,7};
    int high[] = {10,20};
    kdTreePrintRange(root, low, high);
    return 0;
}