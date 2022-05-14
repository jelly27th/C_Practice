/**
 * @file series.c
 * @author 吴国栋 (872908391@qq.com)
 * @brief 求幂
 * @version 0.1
 * @date 2022-05-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdio.h>
#include <math.h>

double series(size_t N, size_t base);
int main(int argc, char **argv)
{
    double sum = series(2,4);
    printf("%f\n",sum);
    return 0;
}

double series(size_t N, size_t base)
{
    double sum = 0;
    double total = 0;
    for (size_t i = 0; i < 100; i++)
    {
        sum = pow(i,N)/pow(base,i);
        total += sum;
    }
    return total;
}