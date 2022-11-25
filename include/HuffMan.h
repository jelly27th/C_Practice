#ifndef _HUFFMAN_H
#define _HUFFMAN_H
#include <stdio.h>

typedef struct _head {
    int Char; // Ascii character
    int count; // The number of times the character appears in the file
    int parent, lch, rch; // make a tree
    char bits[256]; // the huffman code
}_head;

typedef _head head[512];
typedef struct _header {
   head header;
   long num; 
}_header;
typedef _header* HuffManTree;

typedef struct _Code {
    int Char; // Ascii character
    int Length; // Length of huffman code
    char bits[256]; // the huffman code 
}_Code;

typedef _Code Code[128];
typedef struct  _CodeSet {
    Code Set;
    int num;
}CodeSet;
typedef CodeSet* HuffManCode; 

void printfPercent(int per);
int Compress(const char *inputfile,const char *outputfile);
long File_Read(HuffManTree T, FILE* ifp);
void HuffManTree_Init(HuffManTree T);
static void Sort(HuffManTree T);
void HuffManTree_Generate(HuffManTree T);
int File_Compress(HuffManTree T, FILE *ifp, FILE *ofp, long Len);
int UnCompress(const char *inputfile, const char *outputfile);
int HuffManCode_Generate(HuffManCode T, FILE *ifp);
void File_UnCompress(HuffManCode T, FILE *ifp, FILE *ofp, int Len);

#endif