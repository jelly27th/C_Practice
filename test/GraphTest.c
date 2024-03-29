/**
 * @file GraphTest
 * @author Jelly (wugd827@163.com)
 * @brief excrise 9.3
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
    // Topological_Sort(G);
    // Tarjan(G);
    print(G);
    Find_EulerCircuit(G);
    Graph_Delete(G);
    return 0;
}