/**
 * @file repeat.c
 * @author 吴国栋 (872908391@qq.com)
 * @brief 习题3.16
 * @version 0.1
 * @date 2022-05-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>
#include <stdlib.h>
void Delete(int* arr,int sub, int length);
void DeRepeat(int* arr,int length);

int main(int argc, char **argv)
{
    int arr[] = {0,1,1,3,3,5,6,7,7,8,8,9};
    int length = sizeof(arr) / sizeof(arr[0]);
    DeRepeat(arr, length);
    return 0;
}
//数组删除重复元素
//start 0,1,1,3,3,5,6,7,7,8,8,9
//end 0 1 3 5 6 7 8 9
void DeRepeat(int* arr,int length)
{
    for(int i=0;i<length;i++)
    {
        int j = i+1;
        while(j<length)
        {
            if(arr[i]==arr[j]) 
            {
                Delete(arr,j,length);
                length--;
            }
            else j++;
        }

    }
    for (int i=0; i<length; i++)
    {
        printf("%d ",arr[i]);
    }
}
void Delete(int* arr,int sub, int length)
{
    for(int i=sub; i<length; i++) 
        arr[i] = arr[i+1];
}