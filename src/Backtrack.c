#include "Backtrack.h"
#include <stdlib.h>

// Suppose the distance set is sorted from small to large.
// In the distance set D, find a maximum value, if found, return -1.
static int FindMax(int D[], int N) {
    for (int i = N * (N - 1) / 2; i >= 1; i--) {
        if (D[i] != -1) return D[i];
    }
    return -1;
}

// Suppose the distance set is sorted from small to large.
// In the D array of size N, find a number Num, and delete the number (set to -1).
// Returns false if not found.
static bool FindNum(int D[], int N, int Num) {
    for (int i = 1; i <= N * (N - 1) / 2; i++) {
        if (D[i] == Num) {
            D[i] = -1;
            return true;
        }
    }
    return  false;
}

// Copy the elements in the Dset collection to Dtmp.
static void Copy(int Dtmp[], int Dset[], int N) {
    for (int i = 1; i <= N * (N - 1) / 2; i++) {
        Dtmp[i] = Dset[i];
    }
}

// x[] is a collection of points.
// Dset[] is a collection of distance of point to point.
// N is the number of point.
int turnPike(int X[], int Dset[], int N) {
    // Include the largest and smallest points into the vertices.
    X[1] = 0;
    X[N] = Dset[N * (N - 1) / 2];
    // Set the maximum distance to -1, which means empty.
    Dset[N * (N - 1) / 2] = -1;
    return Place(X, Dset, N, 2, N-1);
}

// x[] is a collection of points.
// Dset[] is a collection of distance of point to point.
// N is the number of point.
// left and right are the leftmost and rightmost of X[].
static bool Place(int X[], int Dset[], int N, int Left,int Right) {
    bool found = false, flag = false;
    
    if (Left > Right) return true;
    
    // the maximum value of the current distance set Dset[].
    int Dmax = FindMax(Dset, N);

    // Dtmp[] is a copy of Dset[] for backtracking.
    int* Dtmp = malloc(sizeof(int) * (N * (N - 1) / 2));
    Copy(Dtmp, Dset, N);

    /*First step: try to place DMax at X[right].*/
    //Judge whether the distance of X[i]-DMax is in the set Dtmp[], i ∈ [1, left) 
    for (int i = 1; i < Left; i++) {
        if (!FindNum(Dtmp, N, abs(X[i] - Dmax))) {
            flag = true;
            break;
        }
    }

    //Judge whether the distance of X[i]-DMax is in the set Dtmp[], i ∈ (right, N]
    for (int i = N; i > Right; i--) {
        if (!FindNum(Dtmp, N, abs(X[i] - Dmax))) {
            flag = true;
            break;
        }
    }

    // if Dmax can place in the set X[], recursive next level.
    if (!flag) {
        X[Right] = Dmax;
        found = Place(X, Dtmp, N, Left, Right - 1);
    }

    /*If first attempt failed, try to place X[N] - Dmax at X[left]*/
    if (flag || !found) {
        flag = false;
        //Update Dtmp[] to Dset[] again so that backtrack.
        Copy(Dtmp, Dset, N);

        //Judge whether the distance of X[i] - (X[N] - Dmax) is in the set Dtmp[], i ∈ [1, left) 
        for (int i = 1; i < Left; i++) {
            if (!FindNum(Dtmp, N, abs(X[i] - (X[N] - Dmax)))) {
                flag = true;
                break;
            }
        }

        //Judge whether the distance of X[i] - (X[N] - Dmax) is in the set Dtmp[], i ∈ (right, N]
        for (int i = N; i > Right; i--) {
            if (!FindNum(Dtmp, N, abs(X[i] - (X[N] - Dmax)))) {
                flag = true;
                break;
            }
        }

        // if X[N] - Dmax can place in the set X[], recursive next level.
        if (!flag) {
            X[Left] = X[N] - Dmax;
            found = Place(X, Dtmp, N, Left + 1, Right);
        }
    }
    free(Dtmp);
    return found;
}