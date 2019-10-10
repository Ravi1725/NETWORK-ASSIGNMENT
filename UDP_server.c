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
	char rev_str[MAXLINE];
	//char *hello ="Hello from server";
	struct sockaddr_in server_addr,client_addr;
	//socket
	sock_fd=socket(AF_INET,SOCK_DGRAM,0);
	if(sock_fd<0){
		perror("[-]socket creation failed");
		exit(1);
	}
	else
		printf("[+]Socket Established\n");

	memset(&server_addr, 0, sizeof(server_addr));
	memset(&client_addr, 0, sizeof(client_addr));

	server_addr.sin_family= AF_INET;
	server_addr.sin_addr.s_addr= INADDR_ANY;
	server_addr.sin_port = htons(PORT);
	
	//BIND
	if(bind(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr))<0){
		perror("[-]BIND Failed");
		exit(1);
	}
	else
		printf("[+]BIND Successful\n");

	int n=1;
	while(n){
	int len,n;
	n = recvfrom(sock_fd, (char *)buffer, MAXLINE,MSG_WAITALL, (struct sockaddr *)&client_addr, &len);
	
	int l=strlen(buffer);
	for(int i=0;i<l;i++){
		rev_str[i]=buffer[l-i-1];
	}
	char k=buffer[0];
	//printf("\n %s",rev_str);
	if(k=='\0'){
		n=-1;
	}

	buffer[n]='\0';
	printf("Recieved from client : %s\n",buffer);
	printf("Reversed string is : %s\n",rev_str);
	sendto(sock_fd, (const char *)rev_str, strlen(rev_str),MSG_CONFIRM, (const struct sockaddr *)&client_addr, len);
	printf("Message sent to client\n");
	n++;
	}
	return 0;
}
