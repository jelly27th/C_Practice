## 目录
- [简述](#简述)
- [完成进度](#完成进度)
- [注意事项](#注意事项)
- [索引(英文对应函数名)](#索引英文对应函数名)
  - [第一章](#第一章)
  - [第二章](#第二章)
  - [第三章](#第三章)
  - [第四章](#第四章)
  - [第五章](#第五章)
  - [第六章](#第六章)
  - [第七章](#第七章)
  - [第八章](#第八章)
  - [第九章](#第九章)
  - [第十章](#第十章)
  - [第十一章](#第十一章)
  - [第十二章](#第十二章)
- [参考](#参考)

# 简述
数据结构与算法分析(C语言描述)习题练习,是传说中的黑皮书。

几乎大部分习题都做了，但是很难的和一些经典问题没有做，比如第十章中的N皇后问题之类,书中也只是在习题提了一嘴罢了。
# 完成进度
- [x] 第一章
- [x] 第二章
- [x] 第三章
- [x] 第四章
- [x] 第五章
- [x] 第六章
- [x] 第七章
- [x] 第八章
- [x] 第九章
- [x] 第十章
- [x] 第十一章
- [x] 第十二章

# 注意事项
1. [斐波那契堆](/include/FibonacciHeap.h)无法在VS中构建编译.
2. 还有一些习题的程序我没有标出来，需要自己找。
3. 练习时为避免命名冲突,使用了大量的static关键字，还有命名方式是有点不伦不类的。
# 索引(英文对应函数名)
## 第一章
1. [第一章选择问题](/Chapter/CH_01/sort.c)  
2. [解字谜](/Chapter/CH_01/puzzle.c)
3. [使用I/O的PrintfOut函数输出任意实数](/Chapter/CH_01/PrintfDigit.c)
4. [文件处理](/Chapter/CH_01/file.c)
## 第二章
1. [N个自然数随机置换](/Chapter/CH_02/RandomPermutation.c)
2. [判断素数](/Chapter/CH_02/Prime.c)
3. [非递归求幂(Pow)](/Chapter/CH_02/QuickPower.c)
4. [摩尔投票](/Chapter/CH_02/MainElement.c)
5. [对分查找](/Chapter/CH_02/BinarySearch.c)
6. [最大子序列和](/Chapter/CH_02/MaxSubsequenceSum.c)
## 第三章
1.  [打印链表(PrintNode)](/Chapter/CH_03/LinkedList.c)
2.  [打印链表特定元素(PrintLots)](/Chapter/CH_03/PrintSpecificElements.c)
3.  [单双链表交换元素](/Chapter/CH_03/Swap.c)
4.  [链表交集](/Chapter/CH_03/Intersection.c)
5.  [链表并集](/Chapter/CH_03/Union.c)
6.  [多项式相加(Addition)](/Chapter/CH_03/Polynomial.c)
7.  [多项式相乘(Multiply)](/Chapter/CH_03/Polynomial.c)
8.  [多项式求幂(Power)](/Chapter/CH_03/Polynomial.c)
9.  [任意精度整数运算包](/Chapter/CH_03/IntegerPack.c)
10. [Josephus问题](/Chapter/CH_03/Josephus.c)
11. [寻找单链表特定元素](/Chapter/CH_03/Find.c)
12. [反转单链表](/Chapter/CH_03/Reverse.c)
13. [桶排序](/Chapter/CH_03/BucketSort.c)
14. [链表实现邻接表](/Chapter/CH_03/AdjacencyList.c)
15. [游标实现邻接表](/Chapter/CH_03/Cursor.c)
16. [自调整表](/Chapter/CH_03/SelfAdujstmentTable.c)
17. [删除重复元素](/Chapter/CH_03/repeat.c)
18. [链表懒惰删除](/Chapter/CH_03/LazyDeletetion.c)
19. [检测平衡符号](/Chapter/CH_03/BalanceSymbol.c)
20. [后缀计算值](/Chapter/CH_03/suffix.c)
21. [中缀转后缀含幂操作(InfixToPostfix)](/Chapter/CH_03/convert.c)
22. [后缀转中缀含幂操作(PostfixToInfix)](/Chapter/CH_03/convert2.c)
23. [一个数组实现两个栈](/Chapter/CH_03/TwoStacks.c)
24. [链表实现队列](/Chapter/CH_03/queue.c)
25. [数组实现队列](/Chapter/CH_03/queue2.c)
26. [双端队列](/Chapter/CH_03/deque.c)
## 第四章
1. [二叉树](/Chapter/CH_04/BinarySearchTree.c)
2. [游标实现二叉树](/Chapter/CH_04/CursorBinarySearchTree.c)
3. [二叉树删除四种方法(DeleteLeft、DeleteRight、AlternateDelete、RandomDelete)](/Chapter/CH_04/BinarySearchTree.c)
4. [AVL树](/include/AvlTree.h)
5. [AVL树非递归插入(AvlInsertNoRecursion)](/include/AvlTree.h)
6. [AVL树双旋转(DoubleRoateLeft、DoubleRoateRight)](/include/AvlTree.h)
7. [计算二叉树节点个数(CountNodes)](/include/BinaryTree.h)
8. [计算二叉树树叶个数(CountLeaves)](/include/BinaryTree.h)
9. [计算二叉树满节点个数(CountFull)](/include/BinaryTree.h)
10. [随机生成二叉树(MakeBinaryRandomTree)](/include/BinaryTree.h)
11. [最小AVL树生成(MinAvlTree)](/include/AvlTree.h)
12. [最小完美AVL树生成(MinGenTree)](/include/AvlTree.h)
13. [二叉树范围打印(BinaryPrintRange)](/include/BinaryTree.h)
14. [计算二叉树坐标(Coordinates)](/include/AvlTree.h)
15. [层序遍历(printTree2)](/include/AvlTree.h)
16. [B树](/include/Btree.h)
17. [遍历基本树(BTreeTraverse)](/include/Btree.h)
18. [判断两颗树相似(BinarySimilar)](/include/BinaryTree.h)
19. [线索树](/include/ThreadTree.h)
20. [k(2)-d树](/include/kdTree.h)
## 第五章
1. [线性探测(FindLinear)](/include/HashQuad.h)
2. [平方探测(FindSquare)](/include/HashQuad.h)
3. [双散列插入(FindDoubleHash)](/include/HashQuad.h)
## 第六章
1. [二叉堆](/include/BinHeap.h)
2. [左式堆](/include/LeftHeap.h)
3. [斜堆](/include/SkewHeap.h)
## 第七章
1. [选择算法(QSelect)](/include/Sort.h)
2. [希尔排序(ShellSort含Hibbard、Knuth、Gonnet、Sedgewick序列)](/include/Sort.h)
3. [三值快速排序(QuickSort)](/include/Sort.h)
4. [插入排序(InsertSort)](/include/Sort.h)
5. [堆排序(HeapSort)](/include/Sort.h)
6. [归并排序(MergeSort)](/include/Sort.h)
## 第八章
1. [一般合并(DisjSet_Union)](/include/DisjSet.h)
2. [按大小求并(DisjSet_Union_Size)](/include/DisjSet.h)
3. [按高度合并(DisjSet_Union_Height)](/include/DisjSet.h)
4. [一般寻找(DisjSet_Find)](/include/DisjSet.h)
5. [一般路径压缩寻找(DisjSet_Find_Path)](/include/DisjSet.h)
6. [按秩大小路径压缩寻找(DisjSet_Find_Path_Halving)](/include/DisjSet.h)
## 第九章
1. [拓扑排序(Topological_Sort)](/include/Graph.h)
2. [单发点最短路径问题(Dijkstra)](/include/Table.h)
3. [Kruskal算法(Kruskal)](/include/Edge.h)
4. [欧拉回路(Find_EulerCircuit)](/include/Graph.h)
5.  [强连通分量(Trjan)](/include/Graph.h)
## 第十章
1.  [文件压缩(File_Compress)](/include/Huffman.h)
2.  [文件解压缩(File_Uncompress)](/include/Huffman.h)
3.  [下项合适算法(NextFit)](/include/BinPacking.h)
4.  [首次合适算法(FirstFit)](/include/BinPacking.h)
5. [最佳合适算法(BestFit)](/include/BinPacking.h)
6. [首次合适递减算法(FirstFit_Decreasing)](/include/BinPacking.h)
7. [最佳合适递减算法(BestFit_Decreasing)](/include/BinPacking.h)
8. [最坏合适算法(WorstFit)](/include/BinPacking.h)
9. [最近点对算法(Closest_Point)](include/Point.h)
10. [快速选择(QSelect)](include/Sort.h)
11. [五分中项抽样算法(Median5)](include/Sort.h)
12. [三分中项抽样算法(Median3)](include/Sort.h)
13. [找矩阵最优顺序(OpyMatrix)](/include/Point.h)
14. [寻找最短路径(Dijkstra)](/include/Table.h)
15. [跳跃表(Skiplist)](/include/Skiplist.h)
16. [收费公路重建算法(turnPike)](/include/Backtrack.h)
17. [三连游戏棋(GameStart)](/include/Backtrack.h)
18. [α和β裁剪(FindComp(Human)Move)](/include/Backtrack.h)
## 第十一章
1. [斐波那契堆(FibHeap)](/include/FibonacciHeap.h)
## 第十二章
1.  [红黑树(RBTree)](/include/RBtree.h)
2.  [1-2-3确定性跳跃表(_123_Skiplist)](/include/_123_Skiplist.h)
3.  [treap堆(treap)](/include/treap.h)
4.  [配对堆(PairingHeap)](/include/PairingHeap.h)
# 参考
1. [YinWenAtBIT/Data-Structure](https://github.com/YinWenAtBIT/Data-Structure)
2. [erkekin/Kruskal](https://github.com/YinWenAtBIT/Data-Structure)
3. [参考文章总集](https://www.dong27th.cn/2022/12/17/CandCpp/DataStructureandAlgorithmAnalysis/postscript/)
