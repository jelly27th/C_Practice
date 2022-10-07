/**
 * @file Sort.c
 * @author Jelly (wugd827@163.com)
 * @brief I'm not doing tests for now, maybe not in the future
 * @version 0.1
 * @date 2022-10-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "Sort.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void InsertSort(int A[],int N)
{
    int tmp;
    int P,j;
    for(P=1;P<N;P++) 
    {
        tmp = A[P];
        for(j = P; j>0&&A[j-1]>tmp;j--)
          A[j] = A[j-1];
        A[j] = tmp;
    }
}
// Incremental sort is N/2 
void ShellSort(int A[],int N)
{
    int tmp;
    int i,j;
    for(int Increment=N/2;Increment> 0; Increment /=2)
    {
        for(i = Increment;i<N;i++)
        {
            tmp = A[i];
            for(j=i;j>Increment;j-=Increment)
            {
                if(tmp<A[j-Increment])
                  A[j] = A[j-Increment];
                else
                  break;
                A[j] = tmp;
            }
        }
    }
}

void HeapSort(int A[],int N)
{
  int i;
  for(i = N/2; i >= 0; i--)//build heap
    PercDown(A,i,N);
  for(i=N-1;i>0; i--)
  {
    Swap(&A[0],&A[i]);//delete maximun
    PercDown(A,0,i);
  }
}

static void Swap(int* A,int* B)
{
  int tmp = *A;
  *A = *B;
  *B = tmp;
}

#define LeftChild(i) (2*(i)+1)
static void PercDown(int A[],int i,int N)
{
  int Child;
  int tmp;

  for(tmp=A[i]; LeftChild(i)<N; i = Child)
  {
    Child = LeftChild(i);
    if(Child!=N-1 && A[Child+1]>A[Child])
      Child++;
    if(tmp<A[Child])
      A[i] = A[Child];
    else
      break;
  }
  A[i] = tmp;
}

static void MSort(int A[],int TmpArray[],int Left,int Right)
{
  int Center;

  if(Left<Right)
  {
    Center = (Left+Right)/2;
    MSort(A,TmpArray,Left,Center);
    MSort(A,TmpArray,Center+1,Right);
    Merge(A,TmpArray,Left,Center+1,Right);
  }
}
// the mian function is Msort() and Merge().
void MergeSort(int A[],int N)
{
  int* TmpArray =  malloc(N*sizeof(int));

  if(TmpArray!=NULL)
  {
    Msort(A,TmpArray,0,N-1);
    free(TmpArray);
  }
  else
  {
    printf("No Space for tmp array!!!\n");
    return 0;
  }
}
// Lpos = start of left half,Ppos = start of right half
static void 
Merge(int A[],int TmpArray[],int Lpos,int Rpos,int RightEnd)
{
  int i,LeftEnd,NumElements,TmpPos;

  LeftEnd = Rpos - 1;
  TmpPos = Lpos;
  NumElements = RightEnd - Lpos + 1;

  // main loop
  while(Lpos<=LeftEnd && Rpos<=RightEnd)
  {
    if(A[Lpos]<=A[Rpos]) 
      TmpArray[TmpPos++] = A[Lpos++];
    else
      TmpArray[TmpPos++] = A[Rpos++];
  } 
  while(Lpos<=LeftEnd)//copy rest of first half 
    TmpArray[TmpPos++] = A[Lpos++];
  while(Rpos<=RightEnd)//copy rest of second half
    TmpArray[TmpPos++] = A[Rpos++];

  // copy tmparray back
  for(i=0;i<NumElements;i++,RightEnd--)
    A[RightEnd] = TmpArray[RightEnd];
}

// the mian function is Qsort() and Median3().
void QuickSort(int A[],int N)
{
  Qsort(A,0,N-1);
}
// returns median of left, Center, and Right
// order these and hide the pivot
static int Median3(int A[],int Left,int Right)
{
  int Center = (Left + Right) / 2;

  if(A[Left]>A[Center])
    Swap(&A[Left],&A[Center]);
  if(A[Left]>A[Right])
    Swap(&A[Left],&A[Right]);
  if(A[Center]>A[Right])
    Swap(&A[Center],&A[Right]);

  // Invariant: A[Left] <= A[Center] <= A[Right]
  Swap(&A[Center],&A[Right-1]);//hide pivot
  return A[Right-1];//return pivot
}

#define Cutoff (3)
static void Qsort(int A[], int Left, int Right)
{
  int i,j;
  int Pivot;

  if(Left+Cutoff<=Right)
  {
    Pivot = Median3(A, Left, Right);
    i = Left;j = Right-1;
    for(;;)
    {
      while(A[++i]<Pivot){}
      while(A[--j]>Pivot){}
      if(i<j)
        Swap(&A[i], &A[j]);
      else
        break;
    }
    Swap(&A[i], &A[Right-1]);//restore pivot

    Qsort(A,Left,i-1);
    Qsort(A,i+1,Right);
  }
  else //Do an insertion sort on the subarray
    InsertSort(A+Left,Right-Left+1);
}
/*Place the kth smallest element in the kth position.*/
/*Beacause arrays start at 0, this will be index k-1.*/
void QSelect(int A[],int k,int Left,int Right)
{
  int i,j;
  int Pivot;

  if(Left+Cutoff<=Right)
  {
    Pivot = Median3(A,Left,Right);
    i = Left;j = Right-1;
    for(;;)
    {
      while(A[++i]<Pivot){}
      while(A[--j]>Pivot){}
      if(i<j)
        Swap(&A[i],&A[j]);
      else
        break;
    }
    Swap(&A[i],&A[Right-1]);//Restore Pivot
    
    if(k<=i)
      QSelect(A,k,Left,i-1);
    else if(k>i+1)
      QSelect(A,k,i+1,Right);
  }
  else//Do an Insertion Sort on the subarray
    InsertSort(A+Left,Right-Left+1);
}

#define Increment_len (10)
// generate Hibbard incremental sequence and fixed quantity is 10
static int* Hibbard()
{
  int* H = malloc(Increment_len*sizeof(int));

  if(H!= NULL)
  {
    H[0] = 1;
    for(int i=1; i<Increment_len; i++)
      H[i] = 2*H[i-1]+1;
  }
  else 
    return NULL;

  return H;
}
// Use Hibbard incremental sequence to sort
void ShellSort_Hibbard(int A[],int N)
{
  int tmp;
  int i,j;
  int* Increment = Hibbard();

  for(int k=9;k>=0;k--)
  {
    for(i = Increment[k];i<N;i++)
    {
      tmp = A[i];
      for(j = i;j>Increment[k];j-=Increment[k])
      {
        if(tmp<A[j-Increment[k]])
          A[j] = A[j-Increment[k]];
        else
          break;
        A[j] = tmp;
      }
    }
  }
  free(Increment);
}

// generate Knuth incremental sequence and fixed quantity is 10
static int* Knuth()
{
  int* H = malloc(Increment_len*sizeof(int));

  if(H!= NULL)
  {
    H[0] = 1;
    for(int i=1; i<Increment_len; i++)
     H[i] = 3*H[i-1] + 1;
  }
  else
   return NULL;
  
  return H;
}
// Use Knuth incremental sequence to sort
void ShellSort_Knuth(int A[],int N)
{
  int tmp;
  int i,j;
  int* Increment = Knuth();

  for(int k=9;k>=0;k--)
  {
    for(i = Increment[k];i<N;i++)
    {
      tmp = A[i];
      for(j = i;j>Increment[k];j-=Increment[k])
      {
        if(tmp<A[j-Increment[k]])
          A[j] = A[j-Increment[k]];
        else
          break;
        A[j] = tmp;
      }
    }
  }
  free(Increment);
}
// generate Gonnet incremental sequence and fixed quantity is 10
static int* Gonnet(N)
{
  int* H = malloc(Increment_len*sizeof(int));

  if(H!= NULL)
  {
    H[9] = N/2.2;
    for(int i=8; i>=0; i--)
      H[i] = H[9]/2.2;
  }
  else
   return NULL;
  
  return H;
}
// Use Gonnet incremental sequence to sort
void ShellSort_Knuth(int A[],int N)
{
  int tmp;
  int i,j;
  int* Increment = Gonnet(N);

  for(int k=9;k>=0;k--)
  {
    for(i = Increment[k];i<N;i++)
    {
      tmp = A[i];
      for(j = i;j>Increment[k];j-=Increment[k])
      {
        if(tmp<A[j-Increment[k]])
          A[j] = A[j-Increment[k]];
        else
          break;
        A[j] = tmp;
      }
    }
  }
  free(Increment);
}
// generate Sedgewick incremental sequence and fixed quantity is 10
// Sedgewick incremental sequence is hi=max(9∗4^j−9∗2^j+1,4^j−3∗2^j+1)
static int* Sedgewick()
{
  int* H = malloc(Increment_len*sizeof(int));

  if(H!= NULL)
  {
    int a,b;
    H[0] = 1;
    for(int i=1;i<Increment_len;i++)
    {
      a = 9*pow(4,i)-9*pow(2,i)+1;
      b = pow(4,i)-3*pow(2,i)+1;
      H[i] = a>b?a:b;
    }
  }
  else
   return NULL;
  
  return H;
}
// Use Sedgewick incremental sequence to sort
void ShellSort_Sedgewick(int A[],int N)
{
  int tmp;
  int i,j;
  int* Increment = Sedgewick();

  for(int k=9;k>=0;k--)
  {
    for(i = Increment[k];i<N;i++)
    {
      tmp = A[i];
      for(j = i;j>Increment[k];j-=Increment[k])
      {
        if(tmp<A[j-Increment[k]])
          A[j] = A[j-Increment[k]];
        else
          break;
        A[j] = tmp;
      }
    }
  }
  free(Increment);
}