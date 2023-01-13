#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include<ctype.h>

#define BIG_SIZE 10000
#define SIZE 23
#define PRE 1
#define POST 2


struct Text* findReplace(char* newW,char* oldW,Text* rawData){
    
    //Text* result;
    int i, cnt = 0;
    int newWlen = strlen(newW);
    int oldWlen = strlen(oldW);

    
    for (i = 0; rawData->str[i] != '\0'; i++) {
        if (strstr(&rawData->str[i], oldW) == &rawData->str[i]) {
            cnt++;
  
            i += oldWlen - 1;
        }
    }
    Text* result=(Text*)malloc(sizeof(Text));
    result->str = (char*)malloc(i + cnt * (newWlen - oldWlen) + 1);
  
    i = 0;
    while (*rawData->str) {
        if (strstr(rawData->str, oldW) == rawData->str) {
            strcpy(&result->str[i], newW);
            i += newWlen;
            rawData->str += oldWlen;
        }
        else
            result->str[i++] = *rawData->str++;
    }
  
    result->str[i] = '\0';
    
    //free(rawData);
    result->length=strlen(result->str);
    
    return result;
}