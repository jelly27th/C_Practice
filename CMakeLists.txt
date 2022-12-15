cmake_minimum_required(VERSION 3.22)
project(SortMake)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fexec-charset=GBK")
# Initiate support for the CXX standard
# set(CMAKE_C_STANDARD 11)
# Explicit requirements indicate support for the C standard
# set(CMAKE_C_STANDARD_REQUIRED True)
 
aux_source_directory(src SRC_SUB)
# set(SRC_CUR test/AvlTreeTest.c) # avltree test
# set(SRC_CUR test/StackTest.c) # stack test
# set(SRC_CUR test/SplayTreeTest.c) # splaytree test
# set(SRC_CUR test/BinaryTreeTest.c) # BinaryTree test
# set(SRC_CUR test/BTreeTest.c) # avltree test
# set(SRC_CUR test/ThreadTreeTest.c) # double thread tree test
# set(SRC_CUR test/kdTreeTest.c) # k-d tree test
# set(SRC_CUR test/HashQuadTest.c) # HashQuad test
# set(SRC_CUR test/BinHeapTest.c) # Binary heap test
# set(SRC_CUR test/DisjSetTest.c) # DisjSet test 
# set(SRC_CUR test/GraphTest.c) # Graph test
# set(SRC_CUR test/TableTest.c) # Table test
# set(SRC_CUR test/EdgeTest.c) # Edge test
# set(SRC_CUR test/HuffManTest.c) # HuffMan test
# set(SRC_CUR test/BinPackingTest.c) # Bin Packing Problem test
# set(SRC_CUR test/PointTest.c) # Point Problem test
# set(SRC_CUR test/SkiplistTest.c) # Skiplist test
# set(SRC_CUR test/BacktrackTest.c) # Backtrack Problem Test
# set(SRC_CUR test/fibonacci_heapTest.c) # Fibonacci heap test
# set(SRC_CUR test/RBtreeTest.c) # RedBlackTree test 
# set(SRC_CUR test/_123_SkiplistTest.c) # 1-2-3 Skiplist test
# set(SRC_CUR test/AAtreeTest.c) # AAtree test
set(SRC_CUR test/treapTest.c) # Treap test

add_executable(test ${SRC_SUB} ${SRC_CUR})
include_directories(include)


