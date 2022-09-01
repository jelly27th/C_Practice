cmake_minimum_required(VERSION 3.22)
project(SortMake)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fexec-charset=GBK")
aux_source_directory(src SRC_SUB)
# aux_source_directory(. SRC_CUR)

set(SRC_CUR test/AvlTreeTest.c) # avltree test
# set(SRC_CUR test/StackTest.c) # stack test
# set(SRC_CUR test/SplayTreeTest.c) # splaytree test
# set(SRC_CUR test/BinaryTreeTest.c) # BinaryTree test

add_executable(test ${SRC_SUB} ) # ${SRC_CUR}
include_directories(include)
