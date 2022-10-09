#ifndef _DISJSET_H
#define _DISJSET_H

#define NumSets (17)
typedef int DisjSet[NumSets+1];
typedef int SetType;
typedef int DisjSet_ElementType;

void DisjSet_Init_0(DisjSet S);
void DisjSet_Init_1(DisjSet S);
void DisjSet_Union(DisjSet S,SetType Root1,SetType Root2);
void DisjSet_Union_Size(DisjSet S,SetType Root1,SetType Root2);
void DisjSet_Union_Height(DisjSet S,SetType Root1,SetType Root2);
SetType DisjSet_Find(DisjSet_ElementType X,DisjSet S);
SetType DisjSet_Find_Path(DisjSet_ElementType X,DisjSet S);

#endif