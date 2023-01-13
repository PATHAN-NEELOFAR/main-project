#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include<ctype.h>

#define BIG_SIZE 10000
#define SIZE 23
#define PRE 1
#define POST 2

char* HashHelper(int Num)
{
    //char IntStr[10]="";
    char* IntStr=malloc(sizeof(char)*10);
    int Size=0;
    while(Num)
    {
        int rem=Num%10;
        IntStr[Size]='0'+rem;
        Num=Num/10;
        Size++;
    }
    IntStr[Size]='\0';
    for(int i=0;i<Size/2;i++)
    {
        char ch;
        ch=IntStr[i];
        IntStr[i]=IntStr[Size-i-1];
        IntStr[Size-i-1]=ch;
    }
    //printf("\n\n%s",IntStr);
    
    return IntStr;
}

Text getHashKey(EncryptedData* ed){

   // char* HashFunc(int *EncryText,int Length)
    Text t1;
    int *EncryText = ed->encData;
    int Length = ed->length;
    int temp;
    char BreakStr[2]="_";
    char* HashCode=malloc(sizeof(char)*100);
    //HashCode="";
    strcpy(HashCode,HashHelper(Length));
    strcat(HashCode,BreakStr);
    
    temp=EncryText[0];
    strcat(HashCode,HashHelper(temp));
    strcat(HashCode,BreakStr);
    
    temp=EncryText[1];
    strcat(HashCode,HashHelper(temp));
    strcat(HashCode,BreakStr);
    
    temp=EncryText[Length-3];
    strcat(HashCode,HashHelper(temp));
    strcat(HashCode,BreakStr);
    
    temp=EncryText[Length-2];
    strcat(HashCode,HashHelper(temp));
    strcat(HashCode,BreakStr);
    
    temp=0;
    for(int i=0;i<Length;i++)
    {
        temp+=EncryText[i];
    }
    
    strcat(HashCode,HashHelper(temp));
    // strcat(HashCode,BreakStr);
    // printf("\nHashCode:");
    // printf("\n\n%s",HashCode);
    
    t1.str = HashCode;
    
    return t1;

}