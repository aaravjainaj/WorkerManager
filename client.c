#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<netdb.h>
#include<string.h>
#define MAX 1024
#define Port 8080
#define SA struct sockAddr;
 
int main() 
{ 
         int sockFd,valread;
         char buffer[MAX] = {0};
         char* command = "tcpudp";
         struct sockaddr_in servAddr, clientAddr; 
    	 sockFd = socket(AF_INET, SOCK_STREAM, 0); 
         bzero(&servAddr, sizeof(servAddr)); 
         bzero(&buffer,strlen(buffer));                                           
    	 servAddr.sin_family = AF_INET; 
         servAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
         servAddr.sin_port = htons(Port);
         memset((&servAddr),0,sizeof(servAddr)); 
         inet_pton(AF_INET,"127.0.0.1",&servAddr.sin_addr); 
	 if (connect(sockFd, (struct sockaddr*)&servAddr, sizeof(servAddr)) != 0) 	
	 { 
         	 printf("connection with the server failed...\n"); 
         } 
         else
         send(sockFd,command, strlen(command),0);
	 printf("Command has been sent");
	 valread = read(sockFd,buffer,1024);
	 printf("%s\n",buffer);
  	 close(sockFd);
	 return 0;
}
