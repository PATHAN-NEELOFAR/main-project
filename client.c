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
#include <stdlib.h>
#include <stdbool.h>

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


#if defined(_WIN32)
#include <conio.h>
#endif

void getargv(char* s1,char* s2){
char* str_var;
  
  str_var=(char*)malloc(sizeof(char)*1024);
  
  strcat(str_var,s1);
      strcat(str_var,"\n");
      strcat(str_var,s2);
      
      
       FILE *fptr_nvar;
  
    fptr_nvar = fopen("/home/ubuntu/Desktop/project/argv.txt", "w");

    if (fptr_nvar == NULL) {
        printf("Error!");
        exit(1);
    }
    
    
       fprintf(fptr_nvar, "%s",s1);
       fprintf(fptr_nvar, "%s","\n");
       fprintf(fptr_nvar, "%s",s2);
    free(str_var);
    fclose(fptr_nvar);

}

int main(int argc, char *argv[]) {

#if defined(_WIN32)
    WSADATA d;
    if (WSAStartup(MAKEWORD(2, 2), &d)) {
        fprintf(stderr, "Failed to initialize.\n");
        return 1;
    }
#endif

    if (argc < 3) {
        fprintf(stderr, "usage: tcp_client hostname port\n");
        return 1;
    }

    printf("Configuring remote address...\n");
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_socktype = SOCK_STREAM;
    struct addrinfo *peer_address;
    if (getaddrinfo(argv[1], argv[2], &hints, &peer_address)) {
        fprintf(stderr, "getaddrinfo() failed. (%d)\n", GETSOCKETERRNO());
        return 1;
    }


    printf("Remote address is: ");
    char list_var[1024];
    char address_buffer[100];
    char service_buffer[100];
    int var =1;
    bool isbool = false;
    getnameinfo(peer_address->ai_addr, peer_address->ai_addrlen,
            address_buffer, sizeof(address_buffer),
            service_buffer, sizeof(service_buffer),
            NI_NUMERICHOST);
    printf("%s %s\n", address_buffer, service_buffer);


    printf("Creating socket...\n");
    SOCKET socket_peer;
    socket_peer = socket(peer_address->ai_family,
            peer_address->ai_socktype, peer_address->ai_protocol);
    if (!ISVALIDSOCKET(socket_peer)) {
        fprintf(stderr, "socket() failed. (%d)\n", GETSOCKETERRNO());
        return 1;
    }


    printf("Connecting...\n");
    if (connect(socket_peer,
                peer_address->ai_addr, peer_address->ai_addrlen)) {
        fprintf(stderr, "connect() failed. (%d)\n", GETSOCKETERRNO());
        return 1;
    }
     int recvSock,sendSock,recvN,sendN,bufferSize=1000,acceptSock,clilen;
    recvN = read(acceptSock,service_buffer,bufferSize);
    freeaddrinfo(peer_address);

    printf("Connected.\n");
   
    
    //printf("To send data, enter text followed by enter.\n");
    printf("\n%s\n",service_buffer);

    while(1) {

        fd_set reads;
        FD_ZERO(&reads);
        FD_SET(socket_peer, &reads);
#if !defined(_WIN32)
        FD_SET(0, &reads);
#endif

        struct timeval timeout;
        timeout.tv_sec = 0;
        timeout.tv_usec = 1000;

        if (select(socket_peer+1, &reads, 0, 0, &timeout) < 0) {
            fprintf(stderr, "select() failed. (%d)\n", GETSOCKETERRNO());
            return 1;
        }

        if (FD_ISSET(socket_peer, &reads)) {
            char read[4096];
            int bytes_received = recv(socket_peer, read, 4096, 0);
            if (bytes_received < 1) {
                printf("Connection closed by peer.\n");
                break;
            }
            
            char  *enc;
            
            enc = (char*)malloc(sizeof(char));
            
             if(isbool){

   		 FILE *textfile;
     
               textfile = fopen(read,"r");
             if(textfile == NULL)
               return 1;
     
          while(fgets(enc, 10000, textfile)){
               printf("%s",enc);
             }
             printf("\n");
              printf("%s\n", list_var);
     
              fclose(textfile);

   		}
   		else
   		{	
   			printf("Received (%d bytes): %.*s",bytes_received, bytes_received, read);
   			for(int i = 0 ; i< strlen(read);i++){
   				list_var[i] = read[i];
   			}
   		}
   			
   		free(enc);
           
           
            isbool = true;
        }

#if defined(_WIN32)
        if(_kbhit()) {
#else
        if(FD_ISSET(0, &reads)) {
#endif
		
            char read_new[4096];
            char *temp_var, *temp_var2;
            temp_var = (char *) malloc(sizeof(char)*1024);
            temp_var2 = (char *) malloc(sizeof(char)*1024);
            if (!fgets(read_new, 4096, stdin)) break;
            printf("\n\nSelected Option %s\n", read_new);
            int number_to_send = atoi(read_new); // Put your value
	    int converted_number = htonl(number_to_send);
	    if(number_to_send==4){
	    printf("Enter the word you want to replace\n");
	    scanf("%s",temp_var);
	    printf("Enter the word you want it to be replaced with\n");
	    scanf("%s",temp_var2);
	    
	    getargv(temp_var,temp_var2);
	    send(socket_peer, &converted_number, sizeof(converted_number),0);
	    }
	else{
	
            send(socket_peer, &converted_number, sizeof(converted_number),0);
           
            }
            
        }
    } //end while(1)

    printf("Closing socket...\n");
    CLOSESOCKET(socket_peer);

#if defined(_WIN32)
    WSACleanup();
#endif

    printf("Finished.\n");
    return 0;
}