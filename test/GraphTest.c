/**
 * @file GraphTest
 * @author Jelly (wugd827@163.com)
 * @brief excrise 8.3
 * @version 0.1
 * @date 2022-10-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "Graph.h"

int main(int argc, char **argv)
{
    Graph G = CreateAOV();
    Topological_Sort(G);
    Graph_Delete(G);
    return 0;
}