#ifndef _AATREE_H
#define _AATREE_H
#include <stdlib.h>

typedef int AATREE_ElementType;
typedef struct AANode {
    AATREE_ElementType Element;
    struct AANode* Left;
    struct AANode* Right;
    int Level;
}AANode, *AAtree;
typedef AAtree AAtree_Position;

// Return for failures
static AAtree_Position NullNode = NULL; // Needs more initalization
AAtree AAtree_Init();
static AAtree Skew(AAtree T);
static AAtree Split(AAtree T);
static AAtree_Position SingleLeftRoate(AAtree_Position X);
static AAtree_Position SingleRightRoate(AAtree_Position P);
AAtree AAtree_Insert(AAtree T, AATREE_ElementType Item);
AAtree AAtree_Remove(AAtree T, AATREE_ElementType Item);
void AAtree_Print(AAtree T, int Level);

#endif