#include "Point.h"
#include <stdio.h>

int main(int argc, char **argv) {
    Point T = Point_Init(16);
    printf("actually result is %.2f\n", MinDistance(T, 16));
    printf("%.f\n",Closest_Point(T, 16));
    Point_Delete(T);
}