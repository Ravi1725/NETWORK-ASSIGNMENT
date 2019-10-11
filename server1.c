/*Q. Write a client-server based program using socket programming, where the client after making the connection to the server will send a STRING to the server, and the server will REVERSE the STRING and send the reversed string to the client as its reply. The client should display the reply received from the server. The server should be implemented as a concurrent server, so that multiple clients can connect to the server at the same time. The prototype for the client and server are as below.

$ <Server> <IP address> <Port No>
$ <Client> <IP address of server> <Port no of server> <String to be reversed>*/





#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>

//char reverse_string(char buffer[]){
	//int i;
	//char rev_str[1024];
	//int l=strlen(buffer);
       // for(i=0;i<l;i++){
		//rev_str[i]=buffer[l-1-i];
	//}
	//return(rev_str);
//}

#define PORT 5000

int main(){
	int sock_fd,ret;
	struct sockaddr_in serverAddr;
	char buffer[1024];
	char rev_str[1024];
	pid_t childpid;

	int newsocket;
	struct sockaddr_in newAddr;
	
	sock_fd=socket(AF_INET,SOCK_STREAM, 0);
	if(sock_fd<0){
		printf("[-]Error in connection\n"); 
		exit(1);
	}
	printf("[+]Client Socket has created\n");

	memset(&serverAddr,'\0',sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	
	//BIND
	if(bind(sock_fd,(struct sockaddr*)&serverAddr, sizeof(serverAddr))){
		perror("[-]Bind Failed");
		exit(1);
	}
	else
	{
 		printf("[+]Socket Established.");
	}
	//LISTEN
	
	if(listen(sock_fd, 10) == 0){
		printf("listening....\n");  
	} 
	else{
		printf("[-]Error in binding\n");
	}
	//ACCEPT
	while(1){
	newsocket = accept(sock_fd, (struct sockaddr*)0,0);
	if(newsocket < 0){
		exit(1);
	}
	if((childpid = fork())==0){
		close(sock_fd);
		while(1){
			recv(newsocket, buffer, 1024, 0);
			int i;
       		        int l=strlen(buffer);
       			 for(i=0;i<l;i++){
               		 rev_str[i]=buffer[l-1-i];
			printf("%c",rev_str[i]);
       			 }
			send(newsocket,rev_str,strlen(rev_str),0);

                        memset(rev_str,0,sizeof(rev_str));


			//rev_str=reverse_string(buffer);
			//printf("%s",rev_str);
			
		}
	}
	}


	return 0;
}
