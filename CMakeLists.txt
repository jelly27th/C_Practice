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
set(SRC_CUR test/TableTest.c) # Table test

add_executable(test ${SRC_SUB} ${SRC_CUR})
include_directories(include)


