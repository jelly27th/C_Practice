#include "Point.h"
#include <stdio.h>

int main(int argc, char **argv) {
    // Point T = Point_Init(16);
    // printf("actually result is %.2f\n", MinDistance(T, 16));
    // printf("%.f\n",Closest_Point(T, 16));
    // Point_Delete(T);

    long C[5] = {50, 10, 40, 30, 5};
    long M[5][5], LastChange[5][5];
    OptMatrix(C, 4, M, LastChange); 
    Traceback(1,4,LastChange);

    return 0;
}