#include <stdio.h>
int power(int base, int freq);
double Pow(double x, int n);

int main(int argc, char **argv)
{
    printf("%f",Pow(2,4000));
    return 0;
}
//常规取幂
int power(int base, int freq)
{
    int ploy = 1;
    for (int i = freq; i >= 0; i--)
    {
        ploy *=base;
    }
    return ploy;
}

//快速取幂非递归版
double Pow(double x, int n)
{
    
    double result = 1;
    while (n)
    {
    
        if (n & 1)        //  等价于判断n的末位是不是1
            result *= x;
        n >>= 1;          // 将n右移一位，即遍历原n的二进制的每一位
        x *= x;  // n右移了一位，x补上
    }
    return result;
}