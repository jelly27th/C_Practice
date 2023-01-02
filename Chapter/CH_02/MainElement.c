/**
 * @file MainElement.c
 * @author Jelly (wugd827@163.com)
 * @brief 摩尔投票
 * @version 0.1
 * @date 2023-01-02
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include<stdio.h>

int MainElement(int*arr,int len);

int main() {
    int arr[]={3,3,4,2,4,4,2,4,4};
    printf("%d %d",MainElement(arr,sizeof(arr)/sizeof(arr[0])),sizeof(arr)/sizeof(arr[0]));
    return 0;
}
//摩尔投票算法解主要元素
int MainElement(int*arr,int len)
{
    //边界条件判断，如果数组为空就返回-1
    if(arr==NULL||len==0)
        return -1;
    //先找出主要元素
    int major = arr[0];
    int count = 1;
    for(int i=1;i<len;i++)
    {
        if(arr[i]==major)
            //如果当前元素等于major，count就加1
            count++;
        else
            //否则count就减1，
            count--;
        if(count<0)
        {
            //如果count小于0，说明前面的
            //全部抵消了，这里在重新赋值
            major = arr[i];
            count = 1;
        }
    }
    //下面是判断主要元素是否存在
    count = 0;
    for(int i=0;i<len;i++)
    {
        if(major==arr[i])
        {
        	count++;
            if(count>(len>>1))
                return major;
        }
    }
    return -1;
}