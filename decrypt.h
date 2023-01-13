#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include<ctype.h>

#define BIG_SIZE 10000
#define SIZE 23
#define PRE 1
#define POST 2

Text* decrypt(EncryptedData* encryptData) {
    int *arrEncrypt = encryptData-> encData;
    int arrLen = encryptData-> length;
    int chk=0;
    Text* decryptData = (Text*)malloc(sizeof(Text));
    decryptData -> str = (char*)malloc((arrLen+1)*sizeof(char)); 
    decryptData->length = encryptData->length;
    char *strDecrypt = decryptData -> str;
    strDecrypt[arrLen]='\0';
    for(int i=0;i<arrLen;i++) {
        if(arrEncrypt[i]>100) {
            chk=1;
            break;
        }
    }
    int k=0;
    if(chk==1) {
        for(int i=0;i<arrLen;i++) 
            arrEncrypt[i]%=100;
    }
    for(int i=0;i<arrLen;i++) {
        int arrPtr=arrEncrypt[i];
        if(arrPtr==0) 
            strDecrypt[k]=' ';
        else if(arrPtr>=1 && arrPtr<=26) 
            strDecrypt[k]='a'-1+arrPtr;
        else if(arrPtr>=27 && arrPtr<=52) 
            strDecrypt[k]='A'-27+arrPtr;
        else if(arrPtr==90) 
            strDecrypt[k]='?';
        else if(arrPtr==99)
            strDecrypt[k]='.';
        k++;
    }
    return decryptData;
}