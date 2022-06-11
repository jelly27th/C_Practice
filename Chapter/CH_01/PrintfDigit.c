/**
 * @file PrintfDigit.c
 * @author Jelly (wugd827@163.com)
 * @brief 使用I/O的PrintfOut函数输出任意实数
 * @version 0.1
 * @date 2022-05-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include<stdio.h>

void PrintfOut(double num, int length);

int main(int argc, char **argv)
{
    PrintfOut(7234.2631,3);
    return 0;
}

void PrintfOut(double num, int length)
{
    // 负数部分
   if (num < 0)
   {
       num = -num;
       printf("-");
   }
   //  正数部分
   int pos = num;
   if (pos>=10)
       PrintfOut(pos/10,length);
   printf("%d", pos%10);
   // 小数部分
   num = num-pos;
   if(num!=0)
   {
       printf(".");
       for(int i=0; i <length; i++)
       {
           num = num*10;
       }
       int dec = num;
       if (dec>=10)
           PrintfOut(dec/10,length);
        printf("%d", dec%10);  
   }
   
}