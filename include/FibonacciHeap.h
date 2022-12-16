#ifndef _FIBONACCIHEAP_H_
#define _FIBONACCIHEAP_H_

typedef int Fibonacci_Type;

typedef struct _FibonacciNode
{
    Fibonacci_Type   key;                        // 关键字(键值)
    int degree;                        // 度数
    struct _FibonacciNode* left;    // 左兄弟
    struct _FibonacciNode* right;    // 右兄弟
    struct _FibonacciNode* child;    // 第一个孩子节点
    struct _FibonacciNode* parent;    // 父节点
    int marked;                       //是否被删除第1个孩子(1表示删除，0表示未删除)
}FibonacciNode, *FibNode;

typedef struct _FibonacciHeap{
    int   keyNum;                    // 堆中节点的总数
    int   maxDegree;                // 最大度
    FibNode min;        // 最小节点(某个最小堆的根节点)
    FibNode* cons;    // 最大度的内存区域
}FibonacciHeap, *FibHeap;

static void fib_node_remove(FibNode  node);
static void fib_node_add(FibNode  node, FibNode  root);
static void fib_node_cat(FibNode  a, FibNode  b);
static FibNode  fib_node_make(Fibonacci_Type key);
static void fib_heap_insert_node(FibHeap  heap, FibNode  node);
static FibNode  fib_heap_remove_min(FibHeap  heap);
static void fib_heap_link(FibHeap   heap, FibNode   node, FibNode  root);
static void fib_heap_cons_make(FibHeap   heap);
// static void fib_heap_cons_make(FibHeap   heap);
static void renew_degree(FibNode  parent, int degree);
static void fib_heap_cut(FibHeap  heap, FibNode  node, FibNode  parent);
static void fib_heap_cascading_cut(FibHeap  heap, FibNode  node);
static void fib_heap_decrease(FibHeap  heap, FibNode  node, Fibonacci_Type key);
static void fib_heap_increase(FibHeap  heap, FibNode  node, Fibonacci_Type key);
static FibNode  fib_node_search(FibNode  root, Fibonacci_Type key);
static FibNode  fib_heap_search(FibHeap  heap, Fibonacci_Type key);
static void _fib_heap_delete(FibHeap  heap, FibNode  node);
static void fib_node_destroy(FibNode  node);
static void _fib_print(FibNode  node, FibNode  prev, int direction);

// 创建Fibonacci堆
FibHeap fib_heap_make();
// 新建键值为key的节点，并将其插入到斐波那契堆中
void fib_heap_insert_key(FibHeap  heap, Fibonacci_Type key);
// 删除键值为key的结点
void fib_heap_delete(FibHeap  heap, Fibonacci_Type key);
// 移除最小节点
void fib_heap_extract_min(FibHeap  heap);
// 更新heap的中的oldkey为newkey
void fib_heap_update(FibHeap  heap, Fibonacci_Type oldkey, Fibonacci_Type newkey);
// 将h1, h2合并成一个堆，并返回合并后的堆
FibHeap  fib_heap_union(FibHeap  h1, FibHeap  h2);
// 在斐波那契堆heap中是否存在键值为key的节点；存在返回1，否则返回0。
int fib_heap_contains(FibHeap  heap, Fibonacci_Type key);
// 获取最小节点对应的值(保存在pkey中)；成功返回1，失败返回0。
int fib_heap_get_min(FibHeap  heap, Fibonacci_Type* pkey);
// 销毁斐波那契堆
void fib_heap_destroy(FibHeap  heap);
// 打印"斐波那契堆"
void fib_print(FibHeap  heap);

#endif
