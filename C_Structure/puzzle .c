#include<stdio.h>
#include<string.h>

#define MAXCHAR 4
#define DIRECTION 8
// 列 宽 方向 字符数 二位数组列表
void puzzle(int row, int column,int dir,int maxchar,char (*puzzle)[column]);
char *dict[4] = {"this", "two", "fat", "that"};

int main(int argc, char **argv)
{
    char puzzl[4][4] = {
        {'t', 'h', 'i', 's'},
        {'w', 'a', 't', 's'},
        {'o', 'a', 'h', 'g'},
        {'f', 'g', 'd', 't'}
    };
    int row = sizeof(puzzl[0])/sizeof(puzzl[0][0]);
    int column = sizeof(puzzl)/sizeof(puzzl[0]);
    puzzle(row, column, DIRECTION, MAXCHAR, puzzl);
    return 0;
}

void puzzle(int row, int column,int dir,int maxchar,char (*puzzle)[column])
{
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<column;j++)
        {
            int x = i;
            int y = j;
            for(int k=0;k<dir;k++)
            {
                int catch = 0;
                char str[10];
                for (int l=0;l<maxchar;l++)
                {
                    str[catch] = *(puzzle[x]+y);
                    str[catch+1] = '\0';
                    for (int m=0;m<DIRECTION;m++)
                    {
                        if(strcmp(str,dict[m]) == 0)
                        {
                            printf("%s\n",str);
                        }
                    }
                    catch++;
                    switch(dir)
                    {
                        case 0: x++; break;//从左到右
                        case 1: x--; break;//从右到左
                        case 2: y++; break;//从上到下
                        case 3: y--; break;//从下到上
                        case 4: x++;y++; break;//从左上到右下
                        case 5: x++;y--; break;//从左下到右上
                        case 6: x--;y++; break;//从右上到左下
                        case 7: x--;y--; break;//从右下到左上
                    }
                }
            }
        }
    }
}