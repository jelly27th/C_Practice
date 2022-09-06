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
void ThreadTreeInorder(ThreadTree root);
ThreadTree ThreadTreeInsert(ThreadTree root,ThreadTreeDataType Data);
ThreadTree ThreadTreeDelete(ThreadTree root,ThreadTreeDataType Data);
ThreadTree ThreadTreeDeleteLeaf(ThreadTree root,ThreadTree parent,ThreadTree T);
ThreadTree ThreadTreeDeleteOneChildren(ThreadTree root,ThreadTree parent,ThreadTree T);
ThreadTree ThreadTreeDeleteTwoChildren(ThreadTree root,ThreadTree parent,ThreadTree T);
ThreadTree ThreadTreeFindSucc(ThreadTree T);
ThreadTree ThreadTreeFindPred(ThreadTree T);
ThreadTree ThreadTreeFindMin(ThreadTree T);
ThreadTree ThreadTreeFindMax(ThreadTree T);
ThreadTree ThreadTreeDestory(ThreadTree T);

#endif