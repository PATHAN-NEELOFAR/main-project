#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include<ctype.h>

#define BIG_SIZE 10000
#define SIZE 23
#define PRE 1
#define POST 2


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include<ctype.h>

#define BIG_SIZE 10000
#define SIZE 23
#define PRE 1
#define POST 2


typedef struct Text Text;
typedef struct EncryptedData EncryptedData;
typedef struct IndexedText IndexedText;
typedef struct IndexedTable IndexedTable;

struct Text {
    char* str;
    int length;
};

struct EncryptedData {
    int* encData;
    int encType;
    int length;
};

struct IndexedText {
    char* word;
    int location;
};

struct IndexedTable {
    Text* text;
    IndexedText* words;
    int size;
};


EncryptedData* encrypt(Text* rawData) {
    EncryptedData* encryptArr; 
    encryptArr = malloc(sizeof(EncryptedData));
    encryptArr -> encData = malloc(sizeof(int)*rawData->length);
    encryptArr -> encType = 0; 
    
    for(int traverse=0; traverse < (rawData->length-1); traverse++) {
        char ch=rawData->str[traverse];
        if(ch>='a' && ch<='z') { 
            encryptArr-> encData[traverse]=1+ch-'a';
        } else if(ch>='A' && ch<='Z') {
            encryptArr-> encData[traverse]=27+ch-'A';
        } else if(ch==' ') {   
            encryptArr-> encData[traverse]=0;
        } else if(ch=='.') {   
            encryptArr-> encData[traverse]=99;
        }         
    }
    encryptArr->length = rawData->length;
    return encryptArr;
}

