#include "treap.h"
#include <stdio.h>

int main(int argc, char **argv) {
    Treap T = Treap_Init();
    int arr[] = {10, 85, 15, 70, 20, 60, 30, 50, 65, 80, 90, 40, 5, 55, 35};
    for (int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++) {
        T = Treap_Insert(T, arr[i]);
    }
    Treap_Print(T, 0);
    
    printf("Remove already\n");
    T = Treap_Remove(T, 70);
    Treap_Print(T, 0);
    return 0;
}