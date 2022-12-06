#include "Skiplist.h"

int main(int argc, char **argv) {
    Skiplist S = Skiplist_Generate();
    for (int i = 1; i < 9; i++) {
        Skiplist_Insert(S, i);
    }
    Skiplist_Print(S);
    Skiplist_Delete_Header(S);
    Skiplist_Print(S);
    Skiplist_Free(S);
    return 0;
}