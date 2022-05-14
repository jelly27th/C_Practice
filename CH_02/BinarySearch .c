/**
 * @file BinarySearch .c
 * @author 吴国栋 (872908391@qq.com)
 * @brief 对分查找
 * @version 0.1
 * @date 2022-05-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdio.h>
int BinarySearch(const char arr[],int Ele,int length);
int main(int argc, char **argv)
{
    char arr[10]= {1,2,3,4,5,6,7,8,9,10};
    printf("%d",BinarySearch(arr,8,10));
    return 0;
}

//对分查找
int BinarySearch(const char arr[],int Ele,int length)
{
    int low,mid,high;
    low = 0;
    high = length -1;
    while (low<=high) {
        mid = (high+low)/2;
        if (arr[mid]<Ele)
            low = mid+1;
        else if (arr[mid]>Ele)
            high = mid-1;
        else
            return mid;
    }
    return -1;
}