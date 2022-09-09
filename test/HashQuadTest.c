#include "HashQuad.h"
#include <stdio.h>

int main(int argc, char **argv)
{
    int arr[] = {4371,1323,6173,4199,4344,9679,1989};
    int N = sizeof(arr) / sizeof(arr[0]);

    HashTable H = InitHashTable(10);
    // for(int i = 0; i < N; i++)
    //   HashInsert(arr[i], H,Linear);
    // HashDestory(H);

    // H = InitHashTable(10);
    // for(int i = 0; i < N; i++)
    //   HashInsert(arr[i], H,Square);
    // HashDestory(H);

    // H = InitHashTable(10);
    for(int i = 0; i < N; i++)
      HashInsert(arr[i], H,DoubleHash);
    H = HashDestory(H);
    return 0;
}