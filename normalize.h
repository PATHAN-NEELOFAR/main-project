#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include<ctype.h>

#define BIG_SIZE 10000
#define SIZE 23
#define PRE 1
#define POST 2

Text* normalize(Text* rawData) {
    Text* normalizedData = (Text*)malloc(sizeof(Text));
    normalizedData -> str = (char*)malloc((rawData->length)*sizeof(char));
    char* string = (char*)malloc((rawData->length)*sizeof(char));
    string = rawData -> str;
    int i, j;
    for(i=0; i<rawData->length; i++) {
        if(string[i]==' ' && string[i+1]==' ') {
            for(j=i; j<(rawData->length-1); j++) 
                string[j] = string[j+1];
            string[j] = '\0';
            rawData->length--;
            i--;
        }
      
        else if(string[i]=='.' && string[i+1]=='.') {
            for(j=i; j<(rawData->length-1); j++) 
                string[j] = string[j+1];
            string[j] = '\0';
            rawData->length--;
            i--;
        }
        else if(string[i]==' ' && string[i+1]=='.') {
            for(j=i; j<(rawData->length-1); j++) 
                string[j] = string[j+1];
            string[j] = '\0';
            rawData->length--;
            i--;
        }
        else if(isalpha(string[i]) == 0 && isdigit(string[i])==0 && string[i]!= ' ' && string[i]!= '.')
        {
            for(j=i; j<(rawData->length-1); j++) 
                string[j] = string[j+1];
            string[j] = '\0';
            rawData->length--;
            i--;
        }
        else if(string[i]=='.' && string[i+1]==' ') {
            for(j=i+1; j<(rawData->length-1); j++) 
                string[j] = string[j+1];
            string[j] = '\0';
            rawData->length--;
            i--;
        }
        else if(string[i]=='.' && string[i+1]=='.') {
            for(j=i; j<(rawData->length-1); j++) 
                string[j] = string[j+1];
            string[j] = '\0';
            rawData->length--;
            i--;
        }
   }
   normalizedData->str = string;
   normalizedData->length = rawData->length;
   return normalizedData;
}