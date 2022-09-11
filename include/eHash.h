#ifndef _EHASH_H
#define _EHASH_H

#define MAX_BUCK 4
typedef int BucketType;
struct Bucket{
    BucketType bucket[MAX_BUCK];
    int depth;
    int index;
};
typedef struct Bucket* Bucket;
struct eHash{
    int depth;
    Bucket TheCell;
};
typedef struct eHash* eHash;

eHash eHashInit(int Tablesize);
eHash eHashDestory(eHash H);

#endif