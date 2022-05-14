/**
 * @file sort .c
 * @author 吴国栋 (872908391@qq.com)
 * @brief 四种排序
 * @version 0.1
 * @date 2022-05-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include<stdio.h>

void sort(int arr[], int length);
void insertsort(int *arr, int length);
void shellsort(int *arr,int length);
void selectsort(int *arr, int length);
void bubblesort(int *arr, int length);

int main(void) {
    int arr[] = { 4,3,39,1,20,11,45 };
    bubblesort(arr, sizeof(arr) / sizeof(int));
    return 0;
}

// 最笨的方法
void sort(int arr[], int length)
{
    for (int i = 0; i < length; i++)
    {
        for (int j = i; j < length; j++)
        {
            if (arr[i] >= arr[j])
            {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
    if (length % 2 == 0)
        printf("%d\n", arr[length / 2]);
    else
        printf("%d\n", arr[((length + 1) / 2) - 1]);
}

// 直接插入排序 时间复杂度O(N2)
void insertsort(int *arr, int length)
{
    for (int i = 0; i < length; i++)
    {
        for (int j = i+1 ; j > 0; j--)
        {
            if (j == length) break;//防止数组越界
            if(arr[j]<arr[j-1])
            {
                int temp = arr[j-1];
                arr[j-1] = arr[j];
                arr[j] = temp;
            }
            else
            break;
        }
    }
    if (length % 2 == 0)
        printf("%d\n", arr[length / 2]);
    else
        printf("%d\n", arr[((length + 1) / 2) - 1]);
}

//希尔排序 时间复杂度O(NlogN)
void shellsort(int *arr,int length)
{
    int gap = length/2;
    while(gap)
    {
        for(int i = 0;i < gap; i++)
        {
            if(arr[i]>arr[i+gap])
            {
                int temp = arr[i];
                arr[i] = arr[i+gap];
                arr[i+gap] = temp;
            }
        }
        if(gap==1)
        {
            for (int i = 0; i < length; i++)
            {
                for (int j = i+1 ; j > 0; j--)
                {
                    if (j == length) break;//防止数组越界
                    if(arr[j]<arr[j-1])
                    {
                        int temp = arr[j-1];
                        arr[j-1] = arr[j];
                        arr[j] = temp;
                    }
                    else
                    break;
                }
            }
        }
        gap = gap/2;
    }
    if (length % 2 == 0)
        printf("%d\n", arr[length / 2]);
    else
        printf("%d\n", arr[((length + 1) / 2) - 1]);
}

// 选择排序 时间复杂度O(N2)
void selectsort(int *arr, int length)
{
    for(int i = 0;i<length;i++)
    {
        int start = i;
        int min = start;
        for(int j = i+1;j<length;j++)
        {
            if (arr[min] > arr[j]) min = j;
        }
        if(start!=min)
        {
            int temp = arr[start];
            arr[start] = arr[min];
            arr[min] = temp;
        }
    }
    if (length % 2 == 0)
        printf("%d\n", arr[length / 2]);
    else
        printf("%d\n", arr[((length + 1) / 2) - 1]);
}

// 冒泡排序 时间复杂度O(N2)
void bubblesort(int *arr, int length)
{
    for (int i = length -1; i >= 0; i--)
    {
        for (int j = 0; j < i; j++)
        {
            if (arr[j] > arr[j+1])
            {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
    if (length % 2 == 0)
        printf("%d\n", arr[length / 2]);
    else
        printf("%d\n", arr[((length + 1) / 2) - 1]);
}
