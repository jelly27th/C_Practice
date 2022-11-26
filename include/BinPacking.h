#ifndef _BINPACKING_H
#define _BINPACKING_H

int NextFit(double A[], int N, double Capacity);
int FirstFit(double A[], int N, double Capacity);
int BestFit(double A[], int N, double Capacity);
int WorstFit(double A[], int N, double Capacity);
int FirstFit_Decreasing(double A[], int N, double Capacity);
int BestFit_Decreasing(double A[], int N, double Capacity);
static void Sort(double A[], int N);

#endif