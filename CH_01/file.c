//  实际上没法只能打印当前文件的内容，嵌套的头文件没法打印，因为缺少查找相对路径和绝对路径的方法
/**
 * @file file.c
 * @author 吴国栋 (872908391@qq.com)
 * @brief 头文件索引
 * @version 0.1
 * @date 2022-05-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#define TRUE (1)
#define FALSE (0)
#define MAX_FILENAME (256)
#define MAX_FILEBUFF (MAX_FILENAME + 14)
 
typedef enum row_status 
{
    BEFOR_ROW = 0, 
    BEHIND_ROW, 
    NULL_ROW
}row_status;
// 文件名字
typedef struct file_name
{
    char name[MAX_FILENAME];
    struct file_name *pNext;
}file_name;
 
int isIncludeFiles(char *buff, size_t len, char *fileName, size_t fileNameLen);
// 进程文件
void proccesFile(const char *filename);
void realProccesFile(FILE *fp);
 
int main(void)
{
    proccesFile("G:\\mysql-8.0.27-winx64\\include\\mysql.h");
    return 0;
}
 
void proccesFile(const char *filename)
{
    FILE *fp = NULL;
    static file_name *pFileNameList = NULL;
    file_name *currentFileName = NULL;
    file_name *tmpFileName = NULL;
 
    if(pFileNameList == NULL)
    {
        pFileNameList = malloc(sizeof(file_name));
        strncpy(pFileNameList->name, filename, MAX_FILENAME);//返回最终复制的字符串。
        pFileNameList->pNext = NULL;
        currentFileName = pFileNameList;
        tmpFileName = currentFileName;
    }
    else
    {
        currentFileName = pFileNameList;
        while(currentFileName != NULL)
        {
            if(strcmp(currentFileName->name, filename) == 0)//比较字符串大小
            {
                printf("the #include filename: %s exists!", tmpFileName->name);
                return;
            }
            tmpFileName = currentFileName;
            currentFileName = currentFileName->pNext;
        }
        currentFileName = malloc(sizeof(file_name));
        strncpy(currentFileName->name, filename, MAX_FILENAME - 1);
        currentFileName->pNext = NULL;
        tmpFileName->pNext = currentFileName;
    }
        
    fp = fopen(filename, "r");//只读方式打开文件
    if(fp == NULL)
    {
        tmpFileName->pNext = NULL;
        free(currentFileName);
        printf("failed to open file: %s!\n", filename);
        return;
    }
    realProccesFile(fp);//真正的进程文件
    tmpFileName->pNext = NULL;
    free(currentFileName); 
    return;
}
//从缓冲区打印内容
void printContent(char fileBuff[], size_t len)
{
    size_t index = 0;
 
    while ( index < (len - 1) && fileBuff[index] != '\0' )
    {
        putc(fileBuff[index++], stdout);
    }
 
    return;
}
 
void realProccesFile(FILE *fp)
{
    int ch = 0, tmpch = 0, pre = '\n';
    int i = 0;
    char fileBuff[MAX_FILEBUFF] = {'\0'};
    char subFileName[MAX_FILENAME] = {'\0'};//子文件名
    row_status beforeRow = BEFOR_ROW;
    
    do
    {       
        if(pre == '\n')
        {
            beforeRow = BEFOR_ROW;
        }
 
        ch = getc(fp);
        tmpch = (ch == EOF)? '\n' : ch;
        switch(beforeRow)
        {
            case BEFOR_ROW:
              fileBuff[i++] = tmpch;
              fileBuff[i] = '\0';
              if(tmpch == '\n' || i >= MAX_FILEBUFF - 1)//文件读取结束
              {
                  if(isIncludeFiles(fileBuff, MAX_FILEBUFF, subFileName, MAX_FILENAME) == TRUE)
                  {
                      proccesFile(subFileName);
                      beforeRow = NULL_ROW;  
                  }
                  else
                  {
                      printContent(fileBuff, MAX_FILEBUFF);
                      beforeRow = BEHIND_ROW;
                  }
                  i = 0;
              }
              break;
            case BEHIND_ROW:
              fileBuff[i++] = tmpch;
              fileBuff[i] = '\0';
              if(tmpch == '\n' || i >= MAX_FILEBUFF - 1)
              {
                  printContent(fileBuff, MAX_FILEBUFF);
                  i = 0;
              }
              break;
            case NULL_ROW:
              break;
            default:
              printf("status error, beforeRow: %d!\n", beforeRow);
              break;
        }               
        pre = ch;      
    }while(ch != EOF);  
}
// 包含头文件并存储文件名称
int isIncludeFiles(char *buff, size_t len, char *fileName, size_t fileNameLen)
{
    size_t i = 0, j = 0;
    char head[] = "#include ";
    size_t headLen = sizeof(head)/sizeof(char);
    size_t finalChar = 0;
    size_t beginIndex = 0;
    /*buff字串至少要多*/
    if(headLen + 3 > len)
    {
        return FALSE;
    }
//  判断"#include "是否错误
    for(i = 0; i < headLen - 1; i++)
    {
        if(buff[i] !=  head[i])
        {
            return FALSE;
        }
    }
//  判断是""或<>
    if(buff[i] == '\"')
    {
        finalChar = '\"';
    }
    else if(buff[i] == '<')
    {
        finalChar = '>';
    }
    else
    {
        return FALSE;
    }
    beginIndex = i;
 
    for(++i; i < len; i++)
    {
        if((buff[i] == finalChar))
        {
            if((i - beginIndex - 1) > fileNameLen)
            {
                printf("file name is so long!");
                return FALSE;
            }
            for(++beginIndex; beginIndex < i; beginIndex++)
            {//存储文件名称
                fileName[j++] = buff[beginIndex];
            }
            return TRUE;
        }
    }
 
    return FALSE;
}