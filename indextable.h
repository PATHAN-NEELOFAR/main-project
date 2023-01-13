#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include<ctype.h>

#define BIG_SIZE 10000
#define SIZE 23
#define PRE 1
#define POST 2

IndexedTable* indexWords(Text* textData) {
    IndexedTable* sortedIndexed=(IndexedTable*)malloc(sizeof(IndexedTable));
    sortedIndexed->text=(Text*)malloc(sizeof(Text));
    sortedIndexed->text->str=(char*)malloc(sizeof(char)*(textData->length));
    int r=0,c=0;
    for(int i=0;i<textData->length;i++) {
        char ch=textData->str[i];
        if(ch=='\n' || ch==' ' ||ch=='.' || ch=='\0') {
            r++;
        } 
    } 
    sortedIndexed->size=r;
    sortedIndexed->words=(IndexedText*)malloc((r+1)*sizeof(IndexedText));
    int p=0;
    char tmpl[50]="";
    for(int i=0;i<textData->length;i++) {
        char ch=textData->str[i];
        sortedIndexed->words[p].word = (char*) malloc(strlen(textData->str) * sizeof(char));
        if(ch=='\n' || ch==' ' ||ch=='.' || ch=='\0') 
        {
            tmpl[c]='\0';
            strcpy(sortedIndexed->words[p].word,tmpl);
            sortedIndexed->words[p].location=p;
            p++;
            c=0;
        } else {
            tmpl[c]=ch;
            c++;
        }
    } 
    int temp=0;
    char tm[50]="";
    tm[49]='\0';
    for(int i=0;i<r-1;i++)
    {
        for(int j=0;j<r-i-1;j++)
        {
            if(strlen(sortedIndexed->words[j].word)>strlen(sortedIndexed->words[j+1].word))
            {
                temp = sortedIndexed->words[j].location;
                sortedIndexed->words[j].location = sortedIndexed->words[j+1].location;
                sortedIndexed->words[j+1].location = temp;
                strcpy(tm , sortedIndexed->words[j].word);
                strcpy(sortedIndexed->words[j].word , sortedIndexed->words[j+1].word);
                strcpy(sortedIndexed->words[j+1].word , tm);
            }
            else if(strlen(sortedIndexed->words[j].word)==strlen(sortedIndexed->words[j+1].word))
            {
                if(strcmp(sortedIndexed->words[j].word,sortedIndexed->words[j+1].word)>0)
                    {
                        temp = sortedIndexed->words[j].location;
                        sortedIndexed->words[j].location = sortedIndexed->words[j+1].location;
                        sortedIndexed->words[j+1].location = temp;
                        strcpy(tm , sortedIndexed->words[j].word);
                        strcpy(sortedIndexed->words[j].word , sortedIndexed->words[j+1].word);
                        strcpy(sortedIndexed->words[j+1].word , tm);
                    }
            }
        }
    }
    
    for(int i=0;i<r;i++) {
        strcat(sortedIndexed->text->str, sortedIndexed->words[i].word);
        strcat(sortedIndexed->text->str, " ");
    }
    sortedIndexed->text->length=textData->length;
    return sortedIndexed;
}