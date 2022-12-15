#include "AAtree.h"
#include <stdio.h>

int main(int argc, char **argv) {
    AAtree T = AAtree_Init();
    int arr[] = {10, 85, 15, 70, 20, 60, 30, 50, 65, 80, 90, 40, 5, 55, 35};
    for (int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++) {
        T = AAtree_Insert(T, arr[i]);
    }
    AAtree_Print(T, T->Level);
    
    printf("Remove already\n");
    T = AAtree_Remove(T, 70);
    AAtree_Print(T, T->Level);
    
    return 0;
}