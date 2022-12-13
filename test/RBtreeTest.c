#include "RBtree.h"

int main(int argc, char ** argv) {
    int arr[] = {16, 3, 7, 11, 9, 26, 18, 14, 15};
    RedBlackTree T = RBtree_Init();
    for (int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++) {
        RBtree_Insert(T, arr[i]);
    }
    RBtree_Print(T);
    RBtree_Delete(T, 3);
    RBtree_Print(T);
    RBtree_Free(T);

    return 0;
}