#include "PairingHeap.h"
#include <stdio.h>

int main(int argc, char **argv) {
    PairHeap H = PairHeap_Init();
    PairHeap_Insert(H, 10);
    for (int i = 0; i < 10; i++) {
        H = PairHeap_Insert(H, 2*i);
    }
    // PairHeap_Print(H);
    // printf("First Insert\n");

    for (int i = 0; i < 10; i++) {
        H = PairHeap_Insert(H, 2*i+1);
    }
    // PairHeap_Print(H);
    // printf("Second Insert\n");

    PairHeap_DecreaseKey(H, Location, 3);
    // PairHeap_Print(H);
    // printf("DecreseKey\n");

    int Min;
    H = PairHeap_DeleteMin(&Min, H);
    PairHeap_Print(H);
    printf("DeleteMin\n");

    return 0;
}