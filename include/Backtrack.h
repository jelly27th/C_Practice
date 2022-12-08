#ifndef _Backtrack_H
#define _Backtrack_H
#include <stdbool.h>

static int FindMax(int D[], int N);
static bool FindNum(int D[], int N, int Num);
static void Copy(int Dtmp[], int Dset[], int N);

int turnPike(int X[], int Dset[], int N);
static bool Place(int X[], int Dset[], int N, int Left,int Right);
#endif