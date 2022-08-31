#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"

int main(int argc, char **argv)
{
    int arr[] = {2,1,4,5,9,3,6,7};
    int len = sizeof(arr)/ sizeof(arr[0]);
    Stack S = CreatStack(len);
    for (int i = 0; i < len; i++)
        Push(S,arr[i]);
    printf("%d\n",Top(S));
    Pop(S);
    printf("%d\n",Top(S));
    MakeEmpty(S);
    return 0;
}