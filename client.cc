#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<netdb.h>
#include<string.h>
//#define MAX 1024
using namespace std;
void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char*argv[]) 
{ 
         int sockFd,n;
	 //struct sockaddr_in client_addr;
         //char buffer[MAX] = {0};
         char command[1024];
         struct sockaddr_in serv_addr; 
	 struct hostent *server;
	 char buffer[256];
		    if (argc < 3) {
		       fprintf(stderr,"usage %s hostname port\n", argv[0]);
		       
		    }

	 cout<<"Socket Initialize"<<endl;
	 sleep(1);
    	 sockFd = socket(AF_INET, SOCK_STREAM, 0); 
         bzero(&serv_addr, sizeof(serv_addr)); 
         bzero(&buffer,strlen(buffer));                                           
    	 serv_addr.sin_family = AF_INET; 
         //bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
          serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	 serv_addr.sin_port = htons(8888);
         memset((&serv_addr),0,sizeof(serv_addr)); 
         
	  cout<<"inet_pton is starting"<<endl;
	  sleep(1);
 
	 inet_pton(AF_INET,"127.0.0.1",&serv_addr.sin_addr);

	 cout<<"connect starts"<<endl;
	 sleep(1);
 
	 if (connect(sockFd, (struct sockaddr*)&serv_addr, sizeof(serv_addr))<=0) 	
	 { 
         	 printf("connection with the server failed...\n"); 
         } 
	cout<<"After connection"<<endl;
	sleep(1);
       	bzero(buffer,256);
    	fgets(buffer,255,stdin);
	cout<<"after input"<<endl;
sleep(1);
	write(sockFd, buffer, strlen(buffer));
	cout<<"after write calling"<<endl;
	sleep(1);    	
/*if (n < 0) 
         error("ERROR writing to socket");*/
	bzero(buffer,256);
	cout<<"read starts"<<endl;
	sleep(1);
    	n = read(sockFd, buffer, 255);	
	if (n < 0) 
         error("ERROR reading from socket");
    	printf("%s\n", buffer);
    	close(sockFd);

         //send(sockFd,command, strlen(command),0);
	 //printf("Command has been sent");
	 //int valread = read(sockFd,buffer,1024);
	 //printf("read buffer is running\n");
	 //sleep(1);
	 //close(sockFd);
	 return 0;
}
