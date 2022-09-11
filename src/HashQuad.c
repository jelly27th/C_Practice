#include "HashQuad.h"
#include "Rand.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

HashTable InitHashTable(int Tablesize)
{
    HashTable H = malloc(sizeof(struct HashTb1));

    H->Tablesize = Tablesize;
    H->TheCell = malloc(sizeof(Cell)*H->Tablesize);

    for(int i = 0; i < H->Tablesize; i++)
      H->TheCell[i].Info = Empty;

    return H;
}
// Key is string usually,but for test easily , I use int
HashIndex Hash(HashElementType Key, int Tablesize)
{
    return Key % Tablesize;
}

HashIndex Hash2(HashElementType X)
{
    return R - (X % R);
}

HashIndex HashString(const char* Key, int Tablesize)
{
    unsigned int HashVal = 0;

    while(*Key != '\0')
       HashVal = (HashVal << 5) + *Key++;
    
    return HashVal % Tablesize;
}
// F(i) = i*i and F(i) = F(i-1) + 2i -1 equally
// the function is find empty cell
HashPosition FindSquare(HashElementType Key, HashTable H)
{
    HashPosition CurrentPos;
    int CollisionNum = 0;
    // static int count = 0;

    CurrentPos = Hash(Key, H->Tablesize);
    while(H->TheCell[CurrentPos].Info != Empty &&
          H->TheCell[CurrentPos].Element != Key)
    {
        CurrentPos += 2 * ++CollisionNum -1;
        if(CurrentPos>=H->Tablesize)
           CurrentPos -= H->Tablesize;
        // printf("FindSquare: %d\n", ++count);
    }
    return CurrentPos;
}
// F(i) = i.
// the function is find empty cell.
HashPosition FindLinear(HashElementType Key, HashTable H)
{
    HashPosition CurrentPos;
    int CollisionNum = 0;
    // static int count = 0;

    CurrentPos = Hash(Key, H->Tablesize);
    while(H->TheCell[CurrentPos].Info != Empty &&
          H->TheCell[CurrentPos].Element != Key)
    {
        CurrentPos += 1;
        if(CurrentPos>=H->Tablesize)
           CurrentPos -= H->Tablesize;
        
        // printf("FindLinear: %d\n", ++count);
    }
    return CurrentPos; 
}
// F(i) = i*Hash2(X).
// the function is find empty cell.
HashPosition FindDoubleHash(HashElementType Key, HashTable H)
{
    HashPosition CurrentPos;
    int CollisionNum = 0;
    // static int count = 0;
    // int num = 0;

    CurrentPos = Hash(Key, H->Tablesize);
    while(H->TheCell[CurrentPos].Info != Empty &&
          H->TheCell[CurrentPos].Element != Key)
    {
        CurrentPos += ++CollisionNum * Hash2(Key);
        if(CurrentPos>=H->Tablesize)
           CurrentPos -= H->Tablesize;
        // when you check CurrentPos>=H->Tablesize
        // it means that key can not insert hash table
        // num++;
        if(CurrentPos>=H->Tablesize)
        {
            // count -= num;
            // printf("FindDoubleHash: %d\n", ++count);
            break;
        }
        // printf("FindDoubleHash: %d\n",++count);
    }
    return CurrentPos; 
}
// InsertOfEntry have three types(Linear、Square、DoubleHash).
void HashInsert(HashElementType Key, HashTable H, enum InsertOfEntry Type)
{
    HashPosition Pos;
    switch (Type)
    {
    case Linear: Pos = FindLinear(Key, H);
        break;
    case Square: Pos = FindSquare(Key, H);
        break;
    case DoubleHash: Pos = FindDoubleHash(Key, H);
    default:
        break;
    }
    if(H->TheCell[Pos].Info != Legitmate && Pos < H->Tablesize)
    {
        H->TheCell[Pos].Info = Legitmate;
        H->TheCell[Pos].Element = Key;
    }
}
// 
HashTable HashDestory(HashTable H)
{
	free(H->TheCell);
	free(H);
    return NULL;
}
// We Assume that the output Polynomial terms has known
// I don't test, because it's very trouble
void HashMerge(List T, HashTable H, int Tablesize)
{
    // actually H->Tablesize is H->element
    HashPosition pos = Hash(H->Tablesize,Tablesize);
    // we can understand T->Element is Polynomial terms
    if(H->TheCell[pos].Info !=Empty)
      H->TheCell[pos].Element += T->Element;
    else
      HashInsert(T->Element,H,Linear);
}

