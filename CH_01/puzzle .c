/**
 * @file puzzle .c
 * @author 吴国栋 (872908391@qq.com)
 * @brief 解字谜游戏问题
 * @version 0.1
 * @date 2022-05-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include<stdio.h>
#include<string.h>

#define MAXCHAR 4
#define DIRECTION 8
#define DICTIONARY 4
#define COLUMN 4

void puzzle(int length, int width, int dir,char(*puzzle)[COLUMN]);
int WordFind(int row, int column, int dir, int maxchar, char(*puzzle)[COLUMN]);
//判断数组越界
int bounds(int row, int column);
int rowbounds(int row);
int colbounds(int column);
char* dict[4] = { "this", "two", "fat", "that" };//字典

int main(int argc, char** argv)
{
    char puzzl[4][4] = {
        {'t', 'h', 'i', 's'},
        {'w', 'a', 't', 's'},
        {'o', 'a', 'h', 'g'},
        {'f', 'g', 'd', 't'}
    };
    int length = sizeof(puzzl[0]) / sizeof(puzzl[0][0]);//行
    int width = sizeof(puzzl) / sizeof(puzzl[0]);//列
    puzzle(length, width, DIRECTION,  puzzl);
    return 0;
}

void puzzle(int length, int width, int dir,char(*puzzle)[COLUMN])
{ 
    for (int row = 0; row < length; row++)
    {
        for (int column = 0; column < width; column++)
        {
            for (int k = 0; k < dir; k++)
            {
                WordFind(row,column,k,MAXCHAR,puzzle);
                
            }
        }
    }
}

int WordFind(int row, int column, int dir, int maxchar, char(*puzzle)[COLUMN])
{
    int ct = 0;
    char str[5] = {'0','0','0','0','0' };
    for (int l = 0; l < maxchar; l++)
    {
        str[ct] = *(puzzle[row] + column);
        str[ct + 1] = '\0'; 
        for (int i = 0; i < DICTIONARY; i++)
        {
            if (strcmp(str, dict[i]) == 0)
            {
                printf("%s\n", str);
                return 0;
            }
        }
        ct++;
        switch (dir)
        {
        case 0: row++;if(rowbounds(row)) return 0;break;//从上到下          
        case 1: row--;if(rowbounds(row)) return 0;break;//从下到上          
        case 2: column++;if(colbounds(column)) return 0; break;// //从左到右
        case 3: column--;if(colbounds(column)) return 0; break;//从右到左
        case 4: row++; column++;if(bounds(row,column)) return 0; break;//从左上到右下
        case 5: row++; column--;if(bounds(row,column)) return 0; break;//从左下到右上
        case 6: row--; column++;if(bounds(row,column)) return 0; break;//从右上到左下
        case 7: row--; column--;if(bounds(row,column)) return 0; break;//从右下到左上
        }
    }
    return 0;
}

int bounds(int row, int column)
{
    if (row <= -1 || column <=-1|| row >=5|| column >=5)
    return 1;
    else
    return 0;
}
int rowbounds(int row)
{
    if(row<=-1||row>=5)
    return 1;
    else
    return 0;
}
int colbounds(int column)
{
    if(column<=-1|| column >=5)
    return 1;
    else
    return 0;
}