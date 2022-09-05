#ifndef _THREADTREE_H
#define _THREADTREE_H
#include <stdbool.h>

typedef int ThreadTreeDataType;
typedef struct _ThreadTreeNode ThreadTreeNode;
typedef ThreadTreeNode* ThreadTree;
typedef ThreadTreeNode* ThreadTreePosition;
typedef ThreadTree* ThreadTreeAddress;

struct _ThreadTreeNode{
    ThreadTreeDataType Data;
    // true is thread, false is not thread
    bool RightThread; //right lead line
    bool LeftThread; //left lead line
    ThreadTree Left;
    ThreadTree Right;
};

ThreadTree ThreadTreeFindLeftMost(ThreadTree T);
void ThreadTreeInorder(ThreadTree T);
ThreadTree ThreadTreeInsert(ThreadTree root,ThreadTreeDataType Data);

#endif