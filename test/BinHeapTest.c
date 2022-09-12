#include "BinHeap.h"
#include <stdio.h>

int main(int argc, char **argv)
{
    int arr[] = {10,12,1,14,6,5,8,15,3,9,7,4,11,13,2};
    BinHeap H = BinHeapInit(15);

    for(int i = 0; i <sizeof(arr)/sizeof(arr[0]); i++)
       BinHeapInsert(H,arr[i]);
    BinHeapDeleteMin(H);
    BinHeapDeleteMin(H);
    BinHeapDeleteMin(H);
    
    return 0;
}