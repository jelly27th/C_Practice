#ifndef _SPLAYTREE_H
#define _SPLAYTREE_H

typedef int SplayElementType;
typedef struct _SplayNode SplayNode;
typedef SplayNode* SplayTree;
typedef SplayTree* SplayTreeAdress;
typedef SplayNode* Position;

struct _SplayNode{
    SplayElementType data;
    SplayTree left;
    SplayTree right;
};

SplayTree SplayMakeEmpty(SplayTree T);
Position SplayFind(SplayTree T, SplayElementType element);
Position SplayFindMin(SplayTree T);
Position SplayFindMax(SplayTree T);
SplayTree SplayPreorder(SplayTree T);
SplayTree SplayDelete(SplayTree T, SplayElementType element);
static Position LeftRoate(Position x);
static Position RightRoate(Position y);
SplayTree SplayInsert(SplayTree T, SplayElementType element);
Position Splay(SplayTree T,SplayElementType element);
#endif