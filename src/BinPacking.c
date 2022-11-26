#include "BinPacking.h"
#include <stdio.h>

// printf() can be changed to array linked list storage. 
int NextFit(double A[], int N, double Capacity) {
    int res = 1;
    double bin_rem = Capacity;

    for (int i = 0; i < N; i++) {
        if (A[i] > bin_rem) {
            res++;
            printf(" (");
            bin_rem = Capacity - A[i];
            printf("%.2f", A[i]);
        } else {
            bin_rem -= A[i];
            printf(" %.2f", A[i]);
        }
    }
    return res;
}

// printf() can be changed to array linked list storage. 
int FirstFit(double A[], int N, double Capacity) {
    int res = 0;
    double bin_rem[9];
    for (int i = 0; i < N; i++) {
        int j;
        for (j = 0; j < res; j++) {
            if (bin_rem[j] >= A[i]) {
                bin_rem[j] -= A[i];
                printf("%d: %.2f\n", j, A[i]);
                break;
            }
        }
        if (j == res) {
            bin_rem[res] = Capacity - A[i];
            printf("%d: %.2f\n", res, A[i]);
            res++;
            
        }
    }
    return res;
}

// printf() can be changed to array linked list storage. 
int BestFit(double A[], int N, double Capacity) {
    int res = 0;
    double bin_rem[N], min;
    int j, bi;

    for (int i = 0; i < N; i++) {
        min = Capacity + 0.1;
        bi = 0;

        for (j = 0; j < res; j++) {
            if(bin_rem[j] >= A[i] && bin_rem[j] - A[i] < min) {
                bi = j;
                min = bin_rem[j] - A[i];
            }
        }

        if (min == Capacity + 0.1) {
            bin_rem[res] = Capacity - A[i];
            printf("%d: %.2f\n", res, A[i]);
            res++;
        } else {
            bin_rem[bi] -= A[i];
            printf("%d: %.2f\n", bi, A[i]);
        }
    }
    return res;
}

// printf() can be changed to array linked list storage. 
int WorstFit(double A[], int N, double Capacity) {
    int res = 0;
    double bin_rem[N], max;
    int wi, j;

    for (int i = 0; i < N; i++) {
        max = -1.0, wi = 0;

        for (j = 0; j < res; j++) {
            if (bin_rem[j] >= A[i] && bin_rem[j] - A[i] > max) {
                wi = j;
                max = bin_rem[j] - A[i];
            }
        }

        if (max == -1.0) {
            bin_rem[res] = Capacity - A[i];
            printf("%d: %.2f\n", res, A[i]);
            res++;
        } else {
            bin_rem[wi] -= A[i];
            printf("%d: %.2f\n", wi, A[i]);
        }
    }
    return res;
}

int FirstFit_Decreasing(double A[], int N, double Capacity) {
    Sort(A, N);
    return FirstFit(A, N, Capacity);
}

int BestFit_Decreasing(double A[], int N, double Capacity) {
    Sort(A, N);
    return BestFit(A, N, Capacity);
}

static void Sort(double A[], int N) {
    double tmp;
    for (int i = 0; i < N; i++) {
        for (int j = i+1; j < N; j++) {
            if (A[i] < A[j]) {
                tmp = A[i];
                A[i] = A[j];
                A[j] = tmp;
            }
        }
    }
}