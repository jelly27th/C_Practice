#include "HashQuad.h"
#include <stdio.h>

int main(int argc, char **argv)
{
    int arr[] = {4371,1323,6173,4199,4344,9679,1989};

    HashTable H = InitHashTable(sizeof(arr));
    for(int i = 0; i <sizeof(arr)/sizeof(arr[0]); i++)
      HashInsert(arr[i], H,Linear);
    HashDestory(H);

    HashTable H = InitHashTable(sizeof(arr));
    for(int i = 0; i <sizeof(arr)/sizeof(arr[0]); i++)
      HashInsert(arr[i], H,Square);
    HashDestory(H);

    HashTable H = InitHashTable(sizeof(arr));
    for(int i = 0; i <sizeof(arr)/sizeof(arr[0]); i++)
      HashInsert(arr[i], H,DoubleHash);
    HashDestory(H);
    return 0;
}