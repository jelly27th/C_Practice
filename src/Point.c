#include "Point.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

static double dis(_point T1, _point T2) {
    double x = fabs(T1.x - T2.x);
    double y = fabs(T1.y - T2.y);
    return sqrt(x*x + y*y);
}

static int Compare_X(const void *a, const void *b) {
    return ((_point*)a)->x - ((_point*)b)->x;
}
 
static int Compare_Y(const void *a, const void *b) {
    return ((_point*)a)->y - ((_point*)b)->y;
}

double Closest_Point(Point T, int N) {
    qsort(T->P, N, sizeof(_point), Compare_X);
    Point_Print(T, N);
    return Rec(T, 0, N-1);
}

static double Rec(Point T, int Left, int Right) {
    if (Left == Right) return INF;
    if (Left + 1 == Right) return dis(T->P[Left], T->P[Right]);
    
    int mid = (Left + Right) / 2;
    double dL = Rec(T, Left, mid);
    double dR = Rec(T, mid + 1, Right);
    double d = MIN(dL, dR);

    _point Ltmp[16]; // mid - Left + 1 replace 16
    int lcnt = 0;
    for (int i = Left; i < mid; i++) {
        if (abs(T->P[mid].x - T->P[i].x) <= d) {
            Ltmp[lcnt++] = T->P[i];
        }
    }
    _point Rtmp[16]; // Right - mid replace 16
    int rcnt = 0;
    for (int i = mid + 1; i <= Right; i++) {
        if (abs(T->P[i].x - T->P[mid].x) <= d) {
            Rtmp[rcnt++] = T->P[i];
        }
    }

    qsort(Ltmp, lcnt, sizeof(_point), Compare_Y);
    qsort(Rtmp, rcnt, sizeof(_point), Compare_Y);
    for (int i = 0; i < lcnt; i++) {
        for (int j = 0; j < rcnt; j++) {
            if (abs(Ltmp[i].y -Rtmp[i].y) < d)
                break;
            else if (dis(Ltmp[i], Rtmp[j]) < d) {
                d = dis(Ltmp[i], Rtmp[j]);
            }
        }
    }

    return d;
}

static double MIN(double x, double y) {
    return x < y ? x : y;
}

Point Point_Init(int N) {
    int count = 0;
    double x, y;
    Point T = malloc(sizeof(_Point));
    printf("Please input x coordinates and y coordinates,such as (1,2)\n");
    
    // test data
    _point tmp[16] = {
        {-4, 5}, {1, 4}, {2, -6}, {-1, -1},
        {-6, 3}, {-2, -5}, {6, -2}, {-1, -3},
        {-4, -6}, {-1, 4}, {-3, -3}, {4, -5},
        {5, 2}, {4, 5}, {2, -1}, {-5, -3}
    } ;
    while (count < N) {
        // actual input statement
        // scanf("%f,%f", &x, &y);
        // T->P[count].x = x;
        // T->P[count].y = y;
        T->P[count].x = tmp[count].x;
        T->P[count].y = tmp[count].y;
        count++;
    }

    return T;
}

void Point_Delete(Point T) {
    free(T);
}

void Point_Print(Point T, int N) {
    for (int i = 0; i < N; i++) {
        printf("(%.f, %.f) ", T->P[i].x, T->P[i].y);
    }
    printf("\n");
}

double MinDistance(Point T, int N) {
    double min = INF;
    double tmp;
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            tmp = dis(T->P[i], T->P[j]);
            if (dis(T->P[i], T->P[j]) < min) 
                min = dis(T->P[i], T->P[j]);
        }
    }
    return min;
}

/*
* Compute optimal ordering of matrix multiplication.
* C contains number of columns for each of the N matrices.
* C[0] is the number of rows in matrix 1.
* Minimum number of multiplications is left in M[1][N].
* Actual ordering is computed via.
* another procedure using LastChange.
* M and LastChange are indexed starting at 1, instead of 0.
* Note: Entries below main diagonals of M and LastChange are
* meaningless and uninitialised.
*/
void OptMatrix(const long C[], int N, long M[][MaxSize], long LastChange[][MaxSize]) {
    long ThisM;

    for (int Left = 1; Left <= N; Left++) {
        M[Left][Left] = 0;
    }
    for (int K = 1; K < N; K++) {
        for (int Left = 1; Left <= N -K ; Left++) {
            // for each position    
            int Right = Left + K;
            M[Left][Right] = Infinity;
            for (int i = Left; i < Right; i++) {
                ThisM = M[Left][i] + M[i + 1][Right]
                        + C[Left - 1] * C[i] * C[Right];
                if (ThisM < M[Left][Right]) {
                    // update min
                    M[Left][Right] = ThisM;
                    LastChange[Left][Right] = i;
                } 
            }
        }
    }
}

// Print matrix multiplication optimal path
void Traceback(int i,int j,long LastChange[][MaxSize])
{
	if(i==j) return;
	Traceback(i,LastChange[i][j],LastChange);
	Traceback(LastChange[i][j]+1,j,LastChange);
    printf("Multiply A%d,%ld", i,LastChange[i][j]);
    printf(" and A%ld,%d\n",  LastChange[i][j]+1, j);
}

// Print the path between S and T, except do not print
// the first or last vertex. Print a trailing slash "to" only.
static void PrintPath1(int Path[][MaxSize], int S, int T) {
    int StopOver = Path[S][T];
    if (S != T && StopOver != 0) {
        PrintPath1(Path, S, StopOver);
        printf("%d to",StopOver);
        PrintPath1(Path, StopOver, T);
    }
}

//Assume the existence of a Path of length at least 1 
void PrintPath(int Path[][MaxSize], int S, int T) {
    printf("%d to",S);
    PrintPath1(Path, S, T);
    printf("%d\n",T);
}