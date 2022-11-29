#ifndef _POINT_H
#define _POINT_H

#define INF 10000
typedef struct _point {
    double x, y;
}_point;
typedef _point point[100];
typedef struct {
    point P;
    // int N;
}_Point, *Point;

double Closest_Point(Point T, int N);
static double Rec(Point T, int Left, int Right);
static double dis(_point T1, _point T2);
static int Compare_X(const void *a, const void *b);
static int Compare_Y(const void *a, const void *b);
static double MIN(double x, double y);
Point Point_Init(int N);
void Point_Delete(Point T);
void Point_Print(Point T, int N);
double MinDistance(Point T, int N);

#endif