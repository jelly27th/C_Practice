#ifndef _HASHQUAD_H
#define _HASHQUAD_H
#include "List.h"
#include <stdbool.h>

#define R 7
enum KindOfEntry {
    Legitmate,
    Empty,
    Deleted
};
typedef int HashElementType;
struct HashEntry {
    HashElementType Element;
    enum KindOfEntry Info;
};
typedef struct HashEntry Cell;
struct HashTb1{
    int Tablesize;
    Cell* TheCell;
};
typedef struct HashTb1* HashTable;
typedef unsigned int HashIndex;
typedef HashIndex HashPosition;
enum InsertOfEntry{
    Linear,
    Square,
    DoubleHash
};

HashTable InitHashTable(int Tablesize);
HashIndex Hash(HashElementType Key, int Tablesize);
HashIndex Hash2(HashElementType X);
HashIndex HashString(const char* Key, int Tablesize);
HashPosition FindSquare(HashElementType Key, HashTable H);
HashPosition FindLinear(HashElementType Key, HashTable H);
HashPosition FindDoubleHash(HashElementType Key, HashTable H);
void HashInsert(HashElementType Key, HashTable H, enum InsertOfEntry Type);
HashTable HashDestory(HashTable H);
void HashMerge(List T, HashTable H, int Tablesize);

#endif