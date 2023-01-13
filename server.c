#if defined(_WIN32)
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0600
#endif
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include<ctype.h>

#define BIG_SIZE 10000
#define SIZE 23
#define PRE 1
#define POST 2

#endif


#if defined(_WIN32)
#define ISVALIDSOCKET(s) ((s) != INVALID_SOCKET)
#define CLOSESOCKET(s) closesocket(s)
#define GETSOCKETERRNO() (WSAGetLastError())

#else
#define ISVALIDSOCKET(s) ((s) >= 0)
#define CLOSESOCKET(s) close(s)
#define SOCKET int
#define GETSOCKETERRNO() (errno)
#endif


#include <stdio.h>
#include <string.h>

#include <ctype.h>

//#include "call.h"
#include "encrypt.h"
//#include "call.h"
#include "findreplace.h"
#include "normalize.h"
#include "hashkey.h"
#include "decrypt.h"
#include "getfile.h"
#include "indextable.h"

typedef struct Text Text;
typedef struct EncryptedData EncryptedData;
Text* rawData;
EncryptedData* encryptData;



char* call1(){
	
    	//long int sum;
    rawData = (Text *)malloc(sizeof(Text));
    rawData->str = (char*)malloc(1000*sizeof(char));
    rawData->str  = "COVID crisis has taught us several lessons and together we have overcome this great challenge. The COVID pandemic sent shock waves through the world economy and triggered the largest global economic crisis in more than a century. The crisis led to a dramatic increase in inequality within and across countries. Preliminary evidence suggests that the recovery from the crisis will be as uneven as its initial economic impacts, with emerging economies and economically disadvantaged groups needing much more time to recover from pandemic-induced losses of income and livelihoods. Now there is a sense of introspection in people. India has emerged stronger.";
    rawData->length = strlen(rawData->str);
    encryptData = (EncryptedData *)malloc(sizeof(EncryptedData));
    encryptData = encrypt(rawData); 
    FILE *fptr;
    fptr = fopen("/home/ubuntu/Desktop/project/file1.txt", "w");

    if (fptr == NULL) {
        printf("Error!");
        exit(1);
    }
    for(int i=0; i<encryptData->length; i++)
       fprintf(fptr, "%d ",encryptData->encData[i]);
    
    fclose(fptr);
    return "/home/ubuntu/Desktop/project/file1.txt";
}

char* call2(){
	
    int i=0;
    Text* decryptData = decrypt(encryptData);
    
    FILE *fptr_n;
  
    fptr_n = fopen("/home/ubuntu/Desktop/project/decrypt.txt", "w");

    if (fptr_n == NULL) {
        printf("Error!");
        exit(1);
    }
    
    
       fprintf(fptr_n, "%s",decryptData->str);
    
    fclose(fptr_n);	
  return "/home/ubuntu/Desktop/project/decrypt.txt";
}

char* call5(){
	
    int i=0;
    Text* rawData = (Text*)malloc(sizeof(Text));
    FILE *fptr;
    fptr = fopen("/home/ubuntu/Desktop/project/Text.txt", "r");
    if (fptr == NULL) {
        printf("Error!");
        exit(1);
    }
    fseek(fptr, 0L, SEEK_END);
    rawData->length = (int)ftell(fptr);
    rawData->str = (char*)malloc((rawData->length)*sizeof(char));
    
    rewind(fptr);
    int c = getc(fptr);
    while (c != EOF) {
        rawData->str[i++] = c;
        c = getc(fptr);
    }
    rawData->str[i]='\0';
    fclose(fptr);
    
    Text* normalizedData = normalize(rawData);
    
    FILE *fptr_n;
  
    fptr_n = fopen("/home/ubuntu/Desktop/project/file5.txt", "w");

    if (fptr_n == NULL) {
        printf("Error!");
        exit(1);
    }
    
    for(int i=0; i<normalizedData->length; i++)
       fprintf(fptr_n, "%c",normalizedData->str[i]);
    
    fclose(fptr_n);
  
  return "/home/ubuntu/Desktop/project/file5.txt";
}

char* call3(){

    
    FILE *fptr_n;
    
    fptr_n = fopen("/home/ubuntu/Desktop/project/file3.txt", "w");

    if (fptr_n == NULL) {
        printf("Error!");
        exit(1);
    }
    
    Text hash_key=getHashKey(encryptData);
    
    fprintf(fptr_n, "%s",hash_key.str);
    
    fclose(fptr_n);

	
  return "/home/ubuntu/Desktop/project/file3.txt";
}

char *call4(){

int i_4=0;
    Text* rawData4 = (Text*)malloc(sizeof(Text));
    FILE *fptr;
    fptr = fopen("/home/ubuntu/Desktop/project/argv.txt", "r");
    if (fptr == NULL) {
        printf("Error!");
        exit(1);
    }
    fseek(fptr, 0L, SEEK_END);
    rawData4->length = (int)ftell(fptr);
    rawData4->str = (char*)malloc((rawData4->length)*sizeof(char));
    
    rewind(fptr);
    int c1 = getc(fptr);
    while (c1 != EOF) {
        rawData4->str[i_4++] = c1;
        c1 = getc(fptr);
    }
    rawData4->str[i_4]='\0';
    fclose(fptr);
    
    
 FILE *fptr_n;
    
    fptr_n = fopen("/home/ubuntu/Desktop/project/file4.txt", "w");
    
    if (fptr_n == NULL) {
        printf("Error!");
        exit(1);
    }
    char old[1024],new[1024];
    int var_4 = 0,r=0;
    for(int j = 0; j<=i_4;j++){
    if(rawData4->str[j]!='\n'&& var_4== 0){
    old[j] = rawData4->str[j];
    }
    else if (rawData4->str[j]=='\n'){
    var_4 = 1;
    }
    else if (var_4 == 1){
    new[r++] = rawData4->str[j];
    
    }
    
    }
    
    Text *find_replace= findReplace(new,old,rawData);
    
    fprintf(fptr_n, "%s",find_replace->str);
    
    fclose(fptr_n);
        

return "/home/ubuntu/Desktop/project/file4.txt";
}

char* call6(){
char *file_str6;
file_str6 = (char *)malloc(sizeof(char));


 FILE *fptr_n;
    
    fptr_n = fopen("/home/ubuntu/Desktop/project/file6.txt", "w");

    if (fptr_n == NULL) {
        printf("Error!");
        exit(1);
    }
    
    file_str6 = getfile();
    fprintf(fptr_n, "%s",file_str6);
    
    fclose(fptr_n);
    return "/home/ubuntu/Desktop/project/file6.txt";
}

char* call7(){

FILE *fptr_n;
char *file_str7;

file_str7 = (char *)malloc(sizeof(char));

fptr_n = fopen("/home/ubuntu/Desktop/project/file7.txt", "w");

    if (fptr_n == NULL) {
        printf("Error!");
        exit(1);
    }
    
    file_str7 = getfileh();
    
    fprintf(fptr_n, "%s",file_str7);
    
    fclose(fptr_n);
    return "/home/ubuntu/Desktop/project/file7.txt";
}


char* call8(){
	
    int i=0;
    
    Text *rawData1 = (Text *)malloc(sizeof(Text));
    rawData1->str = (char*)malloc(1000*sizeof(char));
    rawData1->str  = "COVID crisis has taught us several lessons and together we have overcome this great challenge. The COVID pandemic sent shock waves through the world economy and triggered the largest global economic crisis in more than a century. The crisis led to a dramatic increase in inequality within and across countries. Preliminary evidence suggests that the recovery from the crisis will be as uneven as its initial economic impacts, with emerging economies and economically disadvantaged groups needing much more time to recover from pandemic-induced losses of income and livelihoods. Now there is a sense of introspection in people. India has emerged stronger.";
    rawData1->length = strlen(rawData1->str);
    
    FILE *fptr_n1;
  
    fptr_n1 = fopen("/home/ubuntu/Desktop/project/file8.txt", "w");

    if (fptr_n1 == NULL) {
        printf("Error!");
        exit(1);
    }
    
    IndexedTable *sortedIndexed;
    sortedIndexed = (IndexedTable *)malloc(sizeof(IndexedTable));
     sortedIndexed = indexWords(rawData1);

    int charcnt=0;
    for(i=0;i<sortedIndexed->size;i++)
    {
    	charcnt+=strlen(sortedIndexed->words[i].word);
        
        fprintf(fptr_n1,"%s %d\n",sortedIndexed->words[i].word,sortedIndexed->words[i].location);
    } 
    fprintf(fptr_n1,"\nThe total number of words = %d\nThe total number of characters = %d",sortedIndexed->size,charcnt);
    
    fclose(fptr_n1);
    

	
  return "/home/ubuntu/Desktop/project/file8.txt";
}


int main() {

#if defined(_WIN32)
    WSADATA d;
    if (WSAStartup(MAKEWORD(2, 2), &d)) {
        fprintf(stderr, "Failed to initialize.\n");
        return 1;
    }
#endif


    printf("Configuring local address...\n");
    struct addrinfo hints;
    char* hello;
    hello = (char *) malloc(sizeof(char));
    hello = "\n1.Encrypt a text file and return the encrypted information as a file\n2.Decrypt a file data and return the text file\n3.Upload a text file and return the hash key as a file\n4.Find – Replace a text - share the input file and get the processed file.\n5.Normalize a file by eliminating unnecessary white spaces and full stops. All special characters other than white space, full stop and alphabets will be replaced by the code 90.\n6.Organize files by the hash key in the server.\n7.Retrieve the files from the remote server based on the hash key.\n8.Get the word count and the number of characters in a file.\n";
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    struct addrinfo *bind_address;
    getaddrinfo(0, "8080", &hints, &bind_address);


    printf("Creating socket...\n");
    SOCKET socket_listen;
    socket_listen = socket(bind_address->ai_family,
            bind_address->ai_socktype, bind_address->ai_protocol);
    if (!ISVALIDSOCKET(socket_listen)) {
        fprintf(stderr, "socket() failed. (%d)\n", GETSOCKETERRNO());
        return 1;
    }


    printf("Binding socket to local address...\n");
    if (bind(socket_listen,
                bind_address->ai_addr, bind_address->ai_addrlen)) {
        fprintf(stderr, "bind() failed. (%d)\n", GETSOCKETERRNO());
        return 1;
    }
    freeaddrinfo(bind_address);


    printf("Listening...\n");
    if (listen(socket_listen, 10) < 0) {
        fprintf(stderr, "listen() failed. (%d)\n", GETSOCKETERRNO());
        return 1;
    }

    fd_set master;
    FD_ZERO(&master);
    FD_SET(socket_listen, &master);
    SOCKET max_socket = socket_listen;

    printf("Waiting for connections...\n");
 

    while(1) {
        fd_set reads;
        reads = master;
        if (select(max_socket+1, &reads, 0, 0, 0) < 0) {
            fprintf(stderr, "select() failed. (%d)\n", GETSOCKETERRNO());
            return 1;
        }

        SOCKET i;
        for(i = 1; i <= max_socket; ++i) {
            if (FD_ISSET(i, &reads)) {

                if (i == socket_listen) {
                    struct sockaddr_storage client_address;
                    socklen_t client_len = sizeof(client_address);
                    SOCKET socket_client = accept(socket_listen,
                            (struct sockaddr*) &client_address,
                            &client_len);
                    if (!ISVALIDSOCKET(socket_client)) {
                        fprintf(stderr, "accept() failed. (%d)\n",
                                GETSOCKETERRNO());
                        return 1;
                    }
                    
                    send(socket_client, hello, strlen(hello), 0);

                    FD_SET(socket_client, &master);
                    if (socket_client > max_socket)
                        max_socket = socket_client;

                    char address_buffer[100];
                    getnameinfo((struct sockaddr*)&client_address,
                            client_len,
                            address_buffer, sizeof(address_buffer), 0, 0,
                            NI_NUMERICHOST);
                    printf("New connection from %s\n", address_buffer);
                } else {
                    int option;
                    char read[1024];
                    int received_int = 0;

			int return_status = recv(i, &received_int, sizeof(received_int),0);
		if (return_status > 0) {
		
		option = ntohl(received_int);
  			 fprintf(stdout, "Received int = %d\n", ntohl(received_int));
			}
			
			else if (return_status == 0) {
                        FD_CLR(i, &master);
                        CLOSESOCKET(i);
                        continue;}
                    
			
                    printf("Options\n: %d",option);
                   
                    char * read2 = (char *)malloc(sizeof(char));
                   
                    if(isdigit(option)){
                    	if(option<=8)
                    		continue;}
                    else{

                    switch(option){
                    
                    case 1:{
                    read2 = call1();
                    }
                    break;
                    case 2:{
                    read2 = call2();
                    }
                    break;
                    case 3:{
                    read2 = call3();
                    }
                    break;
                    case 4:{
                    read2 = call4();
                    }
                    break;
                    case 5:{
                    read2 = call2();
                    }
                    break;
                    case 6:{
                    read2 = call6();
                    }
                    break;
                    case 7:{
                    read2 = call7();
                    }
                    
                    break;
                    
                    case 8:{
                    read2 = call8();
                    
                    }
                    break;
                    default:{
                    printf("Error!");
                    }
                    
                     }
                }
                
                send(i, read2, 1024, 0);

            } //if FD_ISSET
        } //for i to max_socket
    } //while(1)
}


    printf("Closing listening socket...\n");
    CLOSESOCKET(socket_listen);

#if defined(_WIN32)
    WSACleanup();
#endif


    printf("Finished.\n");

    return 0;
}
