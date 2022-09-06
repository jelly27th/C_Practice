#include <stdio.h>
#include "ThreadTree.h"

int main(int argc, char **argv)
{
    int arr[] = {6,3,1,5,8,7,11,9,13};
    ThreadTree T = NULL;
    for(int i=0; i<sizeof(arr)/sizeof(arr[0]); i++)
    {
        T = ThreadTreeInsert(T,arr[i]);
    }
    ThreadTreeInorder(T);
    ThreadTreeDelete(T,1);
    ThreadTreeInorder(T);
    ThreadTreeDelete(T,3);
    ThreadTreeInorder(T);
    ThreadTreeDelete(T,6);
    ThreadTreeInorder(T);
    T = ThreadTreeDestory(T);
    
    return 0;
}