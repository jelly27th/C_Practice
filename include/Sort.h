#ifndef _SORT_H
#define _SORT_H

void InsertSort(int A[],int N);
void ShellSort(int A[],int N);
void ShellSort_Hibbard(int A[],int N);
void ShellSort_Knuth(int A[],int N);
void ShellSort_Gonnet(int A[],int N);
void ShellSort_Sedgewick(int A[],int N);
void HeapSort(int A[],int N);
void MergeSort(int A[],int N);
void QuickSort(int A[],int N);
void QSelect(int A[],int k,int Left,int Right);
static void Swap(int* A,int* B);
static void MSort(int A[],int TmpArray[],int Left,int Right);
static void Merge(int A[],int TmpArray[],int Lpos,int Rpos,int RightEnd);
static int Median3(int A[],int Left,int Right);
static void Qsort(int A[], int Left, int Right);
static int* Hibbard();
static int* Knuth();
static int* Gonnet(int N);
static int* Sedgewick();
static void PercDown(int A[],int i,int N);

#endif