#include <stdio.h>
#include "Backtrack.h"

int main(int argc, char **argv) {
    int N = 6;
    int X[N + 1];
    int Dset[] = {-1,1,2,2,2,3,3,3,4,5,5,5,6,7,8,10};

    if (turnPike(X, Dset, N)) {
        for (int i = 1; i <= N; i++)
            printf("%d ", X[i]);
        printf("\n");
    } else {
        printf("Not found\n");
    }
} 