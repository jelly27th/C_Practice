#include <string.h>
#include <stdlib.h>
#include "HuffMan.h"

void printfPercent(int per) {
	int i = 0;
	printf("|");
	for (i = 0; i < 10; i++) {
		if(i < per/10)
			printf(">");
		else
			printf("-");
	}
	printf("|complete %d%%\n",per);
}

/*
* The compressed file format is as follows
* FileLength|compressnumber|compresscode|leafnumber|character|length|bits
* FileLength: The total number of characters in the original file.
* compressnumber: The total number of characters in the compressed file (excluding encoding information)
* compresscode: The encoded content of the compressed file
* leafnumber: Huffman tree encoding the number of leaves
* character: Characters represented by Huffman encoding
* length: Length of Huffman character encoding
* bits: Eight-bit Huffman character encoding information
*/
int Compress(const char *inputfile,const char *outputfile) {
    FILE* ifp = fopen(inputfile,"rb");
    if (ifp == NULL) {
        printf("Error: Could not open input file %s\n",inputfile);
        return -1;
    }
    FILE* ofp = fopen(outputfile,"wb");
    if (ofp == NULL) {
        printf("Error: Could not open output file %s\n",outputfile);
        return -1;
    }

    HuffManTree T = malloc(sizeof(_header));
    memset(&T->header, 0, sizeof(_header));
    long FileLength = File_Read(T, ifp);
    HuffManTree_Init(T);
    HuffManTree_Generate(T);
    
    printf("Read the file to be compressed:%s\n",inputfile);
	printf("The current file has:%d character\n",FileLength);
	printf("compressing\n");
    int CompressLength = File_Compress(T, ifp, ofp, FileLength);
    printf("The compressed file is:%s\n",outputfile);
    printf("The compressed file has:%d character\n",CompressLength + 4);

    fclose(ifp);
    fclose(ofp);
    free(T);
}

long File_Read(HuffManTree T, FILE* ifp) {
    long FileLength = 0;
    unsigned char c;
    while (fread(&c, 1, 1, ifp)) {
        // printf("%c", c);
        T->header[c].count++;
        FileLength++;
    }
    return FileLength;
}

void HuffManTree_Init(HuffManTree T) {
    for (int i = 0; i < 512; i++) {
        if (T->header[i].count != 0)
          T->header[i].Char = (unsigned char)i;
        else
          T->header[i].Char = -1;
        T->header[i].parent = -1;
        T->header[i].lch = T->header[i].rch = -1;
    }

    Sort(T);

    for (int i = 0; i < 256; i++) {
        if(T->header[i].count == 0) {
            T->num = i;
            break;
        }
    }
}

static void Sort(HuffManTree T) {
    _head tmp;
    for (int i = 0; i < 256; i++) {
        for (int j = i+1; j < 256; j++) {
            if (T->header[i].count < T->header[j].count) {
                tmp = T->header[i];
                T->header[i] = T->header[j];
                T->header[j] = tmp;
            }
        }
    }
}

void HuffManTree_Generate(HuffManTree T) {
    int min, last;
    for (int i = T->num; i < (2 * T->num -1); i++) {
        // build left child
        min = 9999;
        for (int j = 0; j < i; j++) {
            if (T->header[j].parent != -1) 
               continue;
            if (min > T->header[j].count) {
                last = j;
                min = T->header[j].count;
                continue;
            }
        }
        T->header[i].count = T->header[last].count;
        T->header[last].parent = i;
        T->header[i].lch = last;

        // Build right child
        min = 9999;
        for (int j = 0; j < i; j++) {
            if (T->header[j].parent != -1) 
               continue;
            if (min > T->header[j].count) {
                last = j;
                min = T->header[j].count;
                continue;
            }
        }
        T->header[i].count += T->header[last].count;
        T->header[last].parent = i;
        T->header[i].rch = last;  
    }
    // Set encoding of HUFFMAN tree characters
    int cur, per, len;
    for (int i = 0; i < T->num; i++) {
        cur = i;
        T->header[i].bits[0] = 0;
        while (T->header[cur].parent != -1) {
            per = cur;
            cur = T->header[cur].parent;
            if (T->header[cur].lch == per) {
                len = strlen(T->header[i].bits);
                memmove(T->header[i].bits + 1, T->header[i].bits, len + 1);
                T->header[i].bits[0] = '0';
            } else {
                len = strlen(T->header[i].bits);
                memmove(T->header[i].bits + 1, T->header[i].bits, len + 1);
                T->header[i].bits[0] = '1';
            }
            
        }
    }
}

int File_Compress(HuffManTree T, FILE *ifp, FILE *ofp, long Len) {
    fseek(ifp, 0, SEEK_SET);
    fseek(ofp, 8, SEEK_SET);

    unsigned char c;
    char buf[512] = {0};
    int per = 10, CurPer = 0;
    int len, i;
    long FileLength = 8;
    // Convert the ascii characters of the original file to Huffman encoding
    while (!feof(ifp)) {
        c = fgetc(ifp);
        CurPer++;
        for (i = 0; i < T->num; i++) {
            if (c == T->header[i].Char) break;
        }
        strcat(buf, T->header[i].bits);

        len = strlen(buf);
        c = 0;
        // Convert Huffman encoding into a bit stream.
        // (actually a Huffman encoding a single char to store a bit)
        while (len >= 8) {
            for (i = 0; i < 8; i++) {
                if (buf[i] == '1') c = (c << 1) | 1;
                else c = c << 1; 
            }
            fwrite(&c, 1, 1, ofp);
            FileLength++;
            strcpy(buf, buf + 8);
            len = strlen(buf);
        }
        // Show progress
        if (100 * CurPer /Len > per) {
                printfPercent(per);
                per += 10;
        }
        if (CurPer == Len) break;
    }
    printfPercent(100);

    // When there are less than eight characters remaining.
    if (len > 0) {
        strcat(buf, "00000000");
        for (i = 0; i < 8; i++) {
                if (buf[i] == '1') c = (c << 1) | 1;
                else c = c << 1; 
        }
        fwrite(&c, 1, 1, ofp);
        FileLength++;
    }

    // Write the number of characters in the original file 
    // and the number of compressed characters.
    fseek(ofp, 0, SEEK_SET);
    fwrite(&Len, 1, sizeof(Len), ofp);
    fwrite(&FileLength, sizeof(FileLength), 1, ofp);

    // Write Huffman encoding information to the output document.
    fseek(ofp, FileLength, SEEK_SET);
    fwrite(&T->num, sizeof(T->num), 1, ofp);
    for (int i = 0; i < T->num; i++) {
        fwrite(&(T->header[i].Char), 1, 1, ofp);
        FileLength++;

        len = strlen(T->header[i].bits);
        fwrite(&len, 1, 1, ofp);
        FileLength++;

        if (len % 8 != 0) {
            for (int j = len % 8; j < 8; j++)
                strcat(T->header[i].bits, "0");
        }

        while (T->header[i].bits[0] != 0) {
            c = 0;
            for (int j = 0; j < 8; j++) {
                if (T->header[i].bits[j] == '1') 
                    c = (c << 1) | 1;
                else 
                    c = c << 1;
            }
            strcpy(T->header[i].bits, T->header[i].bits + 8);
            fwrite(&c, 1, 1, ofp);
            FileLength++;
        }
    }
    return FileLength;
}

int UnCompress(const char *inputfile, const char *outputfile) {
    FILE* ifp = fopen(inputfile,"rb");
    if (ifp == NULL) {
        printf("Error: Could not open input file %s\n",inputfile);
        return -1;
    }
    FILE* ofp = fopen(outputfile,"wb");
    if (ofp == NULL) {
        printf("Error: Could not open output file %s\n",outputfile);
        return -1;
    }

    fseek(ifp,0,SEEK_END);
	int len = ftell(ifp);

    printf("The unpacked file will be read:%s\n",inputfile);
	printf("The current file has:%d character\n",len);
	printf("decompressing\n");

    HuffManCode T = malloc(sizeof(CodeSet));
    memset(&T->Set, 0, sizeof(Code));
    int FileLength = HuffManCode_Generate(T,ifp);
    File_UnCompress(T,ifp,ofp,FileLength);

	printf("After decompression, the file is:%s\n",outputfile);
    printf("After decompression, the file has:%d character\n",FileLength);

    fclose(ifp);
    fclose(ofp);
    free(T);
}

int HuffManCode_Generate(HuffManCode T, FILE *ifp) {
    int FileLength, offset;
    int num, len;
    unsigned char c;

    fseek(ifp, 0, SEEK_SET);
    fread(&FileLength,sizeof(long), 1, ifp);
    fread(&offset,sizeof(long), 1, ifp);

    fseek(ifp, offset, SEEK_SET);
    fread(&num,sizeof(long), 1, ifp);
    T->num = num;
    
    int m, tmp;
    char buf[255];
    for (int i=0; i<num; i++) {
        fread(&(T->Set[i].Char), 1, 1, ifp);
        fread(&c, 1, 1, ifp);
        len = (int)c;
        T->Set[i].Length = len;
        T->Set[i].bits[0] = 0;

        if (len % 8 > 0 ) m = len / 8 + 1;
        else m = len / 8;
        for (int j = 0; j < m; j++) {
            fread(&c, 1, 1, ifp);
            tmp = c;
            _itoa(tmp, buf, 2);
            tmp = strlen(buf);
            //Insufficient number of digits, perform zero-fill operation
            for (int k = 8; k > tmp; k--) 
                strcat(T->Set[i].bits, "0");
            strcat(T->Set[i].bits, buf);
        }
        T->Set[i].bits[len] = 0;
    }
    return FileLength;
}

void File_UnCompress(HuffManCode T, FILE *ifp, FILE *ofp, int Len) {
    char buf[255], bx[255];
    int CurPer = 0, per = 10;
    int i, tmp, len1, num = T->num;
    unsigned int len = strlen(T->Set[num-1].bits);
    unsigned char c;

    fseek(ifp, 8, SEEK_SET);
    bx[0] = 0;
    // Read compressed files and convert
    while (CurPer != Len) { 
        while (strlen(bx) < len) {
            fread(&c, 1, 1, ifp);
            tmp = c;
            _itoa(tmp, buf, 2);
            len1 = strlen(buf);
            for (int j = 8; j > len1; j--) {
                strcat(bx, "0");
            }
            strcat(bx, buf);
        }
        for (i = 0; i < num; i++) {
            if (memcmp(T->Set[i].bits, bx, T->Set[i].Length) == 0)
                break;
        }
        strcpy(bx, bx + T->Set[i].Length);
        c = T->Set[i].Char;
        fwrite(&c, 1, 1, ofp);
        CurPer++;

        // Show progress
        if (100 * CurPer / Len > per) {
            printfPercent(per);
            per += 10;
        }
    }
    printfPercent(100);
} 