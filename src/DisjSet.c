/**
 * @file DisjSet.c
 * @author Jelly (wugd827@163.com)
 * @brief the basic routine for DisjSet and excrise 8.3
 * @version 0.1
 * @date 2022-10-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "DisjSet.h"


void DisjSet_Init_0(DisjSet S)
{
    for(int i = NumSets; i > 0; i--)
      S[i] = 0;
}
// it apply in DisjSet_Union_Size() and DisjSet_Union_Height()
void DisjSet_Init_1(DisjSet S)
{
    for(int i = NumSets; i > 0;i--)
      S[i] = -1;
}
// Assume that Root1 and Root2 are roots
// union is a C keyword, so this routine
// is name DisjSet_Union
void DisjSet_Union(DisjSet S,SetType Root1,SetType Root2)
{
    S[Root2] = Root1;
}
// Assume that Root1 and Root2 are roots
// big size root will be attached to small size root  
void DisjSet_Union_Size(DisjSet S,SetType Root1,SetType Root2)
{
    if(S[Root1]<S[Root2])
    {
        S[Root1] += S[Root2];
        S[Root2] = Root1;
    }
    else
    {
        S[Root2] += S[Root1];
        S[Root1] = Root2;
    }
}
// Assume that Root1 and Root2 are roots
// low height Root will be attached to high height Root
// if Root1's height and Root2's height are same, Root1 will be attached to Root2
void DisjSet_Union_Height(DisjSet S,SetType Root1,SetType Root2)
{
    if(S[Root2]<S[Root1])//Root2 is deeper Set
      S[Root1] = Root2; //Make Root2 new root 
    else
    {
        if(S[Root1]==S[Root2]) //Same height
           S[Root1]--; //Update Height
        S[Root2] = Root1;
    }
}
// just find the root node of x, do nothing
SetType DisjSet_Find(DisjSet_ElementType X,DisjSet S)
{
    if(S[X]<=0) return X;
    else return DisjSet_Find(S[X],S);
}

// find the root of x and 
// The parent node of each node passed from x becomes the root node
SetType DisjSet_Find_Path(DisjSet_ElementType X,DisjSet S)
{
    if(S[X]<=0) return X;
    else return S[X]=DisjSet_Find_Path(S[X],S);
}

// find the root of x and 
// Every node from x to the root points to its grandparent
// note: I haven't actually tested this function
SetType DisjSet_Find_Path_Halving(DisjSet_ElementType X,DisjSet S)
{
    while(S[X]>0&&S[S[X]]>0)
    {
        S[X] = S[S[X]];
        X = S[X];
    }

    if(S[X]>0) //if S[X] is the child of the root
      X = S[X];
    
    return X;
}