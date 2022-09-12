#include "BinHeap.h"
#include <stdio.h>

int main(int argc, char **argv)
{
    int arr[] = {10,12,1,14,6,5,8,15,3,9,7,4,11,13,2};
    int arr1[] = {150,80,40,30,10,70,110,100,20,90,60,50,120,140,130};
    BinHeap H = BinHeapInit(15);

    // for(int i = 0; i <sizeof(arr)/sizeof(arr[0]); i++)
    //    BinHeapInsert(H,arr[i]);
    // BinHeapPrint(H);
    // BinHeapDeleteMin(H,1);
    // BinHeapDeleteMin(H,1);
    // BinHeapDeleteMin(H,1);
    // BinHeapPrint(H); 
    
    for(int i=0;i<sizeof(arr)/sizeof(arr[0]); i++)
      H->Elements[i] = arr[i];
    H->Size = 15;
    BinHeapBuildHeap(H); 
    BinHeapPrint(H);
    BinHeapIncreaseKey(H,15,2);
    BinHeapPrint(H);
    BinHeapDecraseKey(H,25,2);
    BinHeapPrint(H);
    BinHeapDecraseKey(H,NONE,1);
    BinHeapPrint(H);
    BinHeapDelete(H,3);
    BinHeapPrint(H);
    BinHeapDestory(H);
    return 0;
}