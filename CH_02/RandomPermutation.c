#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<windows.h>

#define LOWER 1
#define UPPER 10
int RandInt(int lower, int upper);
void Random(int *arr,int lower, int upper);
void Random1(int *arr,int lower, int upper);
void Random2(int *arr,int lower, int upper);
void Swap(int *a, int *b);

int main(int argc, char ** argv) {

    clock_t start, finish;  
    double  duration;  
    int arr[40000] = {0};

    start = clock();  
    Random1(arr,1,40000);
    finish = clock();  
    duration = (double)(finish - start) / CLOCKS_PER_SEC;  
    printf( "%f seconds\n", duration );  

    return 0;
}

int RandInt(int lower, int upper) 
{
    srand((unsigned)time(NULL));
    Sleep(1000);//滞后1S
    return rand() % upper+lower;
}

// 复杂度为O(N2logN)
void Random(int *arr,int lower, int upper)
{
    int i = 0;
    while (i < upper)
    {
        int temp = RandInt(lower, upper);
        BOOL flag = 1;
        for (int j = 0; j <=i; j++)
        {
            if(arr[j]==temp)
            {
                flag = 0;
            }
        }
        if(flag)
        {
            arr[i] = temp;
            i++;
        } 
    }
    for ( i = 0; i < upper; i++)
    {
        printf("%d ", arr[i]);
    }

}
// 复杂度为O(NlogN)
void Random1(int *arr,int lower, int upper)
{
    int *used = (int*)malloc( upper*sizeof(int) );
    for ( int i = 0; i < upper; i++ )
    {
        used[i] = 0;
        printf("%d %d\n", used[i],i);
    }
    int i = 0;
    while (i < upper)
    {
        int temp = RandInt(lower, upper);
        printf("temp=%d\n", temp);
        if(used[temp-1]==0)
        {
            used[temp-1] =1;
            arr[i] = temp;
            printf("arr %d=%d\n",i,temp);
            i++;
        }
    }
    for ( i = 0; i < upper; i++)
    {
        printf("%d ", arr[i]);
    }
    free(used);
}
// 复杂度为O(N)
void Random2(int *arr,int lower, int upper)
{  
    // 装数
    for ( int i = 0; i < upper; i++)
    {
        arr[i] = i+1;
    }
    //随机换数
    for ( int i = 1; i < upper; i++)
    {
        Swap(&arr[i], &arr[RandInt(0,i)]);
    }
    // 打印数
    for (int i = 0; i < upper; i++)
    {
        printf("%d ", arr[i]);
    }
}
void Swap(int *a,int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}