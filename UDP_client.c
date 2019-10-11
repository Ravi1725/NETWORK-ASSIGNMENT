#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 5000
#define MAXLINE 1024

int main(){
	int sock_fd;
	char buffer[MAXLINE];
	char buffer1[MAXLINE];
	char *hello ="Hello from client";
	struct sockaddr_in server_addr;
	FILE *fp;

	fp=fopen("msg.txt","r");

	if(fp == NULL){
		printf("FILE DOES NOT EXIST\n");
	}
	else
		printf("File Created\n");

	//socket Establishment 
	sock_fd=socket(AF_INET,SOCK_DGRAM,0);
	if(sock_fd<0){
		perror("[-]socket establishment failed\n");
		exit(1);
	}
	else
		printf("[+]Socket EStablished\n");

	memset(&server_addr, 0, sizeof(server_addr));

	//server information
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(PORT);
	server_addr.sin_addr.s_addr=INADDR_ANY;

	printf("reached here\n");
	while(!(feof(fp))){
	int n,len;
	fscanf(fp,"%s",buffer);
	//printf("%s",buffer);
	sendto(sock_fd,(const char*)buffer, strlen(buffer),MSG_CONFIRM,(const struct sockaddr *)&server_addr, sizeof(server_addr));
	printf("\nMessage has been sent from client:   %s\n", buffer);
	buffer[0]= '\0';
	n= recvfrom(sock_fd, (char *)buffer1, MAXLINE, MSG_WAITALL, (struct sockaddr *)&server_addr, &len);
	printf("\nMessage recieved from Server :  %s\n",buffer1);
	buffer1[0]= '\0';
	}

	close(sock_fd);
	fclose(fp);
	return 0;
}
