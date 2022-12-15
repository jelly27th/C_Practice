#include "_123_Skiplist.h"
#include <stdio.h>

int main(int argc, char **argv) {
    int arr[] = {5, 10, 15, 20, 25, 30, 35, 40, 45, 50};
    SkipList_123 L = SkipList_123_Init();
    for (int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++) {
        L = SkipList_123_Insert(L, arr[i]);
    }
    SkipList_123_Print(L);
    printf("\n");
    L = SkipList_123_Remove(L, 5);
    SkipList_123_Print(L);
    printf("\n");
    L = SkipList_123_Remove(L, 20);
    SkipList_123_Print(L);

    return 0;
}