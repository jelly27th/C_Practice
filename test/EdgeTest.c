/**
 * @file EdgeTest.c
 * @author Jelly (wugd827@163.com)
 * @brief excrise 9.18
 * @version 0.1
 * @date 2022-10-17
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "Edge.h"

int main(int argc, char **argv)
{
    /*
    * test data
    * (6,9)
    * (5,1,7)
    * (5,3,8)
    * (1,2,6)
    * (1,3,3)
    * (3,2,4)
    * (3,4,3)
    * (2,4,2)
    * (2,6,5)
    * (4,6,2)
    * actually result is
    * 2->4  weight:2
    * 4->6  weight:2
    * 1->3  weight:3
    * 3->4  weight:3
    * 5->1  weight:7
    */
    Edge G = Edge_Init();
    Edge MinTree = Kruskal(G);
    Edge_Print(MinTree);
    return 0;
}