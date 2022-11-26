#include <stdio.h>
#include "BinPacking.h"

int main(int argc, char **argv) {
    double A[] = {0.5, 0.7, 0.5, 0.2, 0.4, 0.2, 0.5, 0.1, 0.6};
    double Capacity = 1.0;
    int N = sizeof(A)/ sizeof(A[0]);
    // printf("\nNumber of bins required in Next Fit: %d\n", NextFit(A, N, Capacity));
    // printf("\nNumber of bins required in First Fit: %d\n", FirstFit(A, N, Capacity));
    // printf("\nNumber of bins required in Best Fit: %d\n", BestFit(A, N, Capacity));
    // printf("\nNumber of bins required in Worst Fit: %d\n", WorstFit(A, N, Capacity));
    // printf("\nNumber of bins required in First Fit Decreasing: %d\n", FirstFit_Decreasing(A, N, Capacity));
    printf("\nNumber of bins required in Worst Decreasing: %d\n", BestFit_Decreasing(A, N, Capacity));
    return 0;
}