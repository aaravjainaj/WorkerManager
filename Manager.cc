#include<stdio.h>
#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<errno.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<queue>
#include "Manager.h"
#include "Worker.h"
using namespace std;


Manager *Manager::mpInstance = NULL;

Manager::Manager() : mIsFinalized (false)
{
	cout<<"Manager Constructor"<<endl;
	sleep(1);
	for (int i = 0; i < 4; ++i)
	{
		mWorkers[i] = new Worker(i);
	}
}

bool
Manager::Initialize()
{
	printf("Manager Initialize\n");
	sleep(1);
	Manager* manager = manager->GetInstance();
		
	for(int i=0;i<4;i++)
	{
		manager->getWorker(i)->Initialize();
		cout<<"Worker "<< i <<" Initialize\n"<<endl;			
	}	
	
	cout << "Calling Thread Initializer " << endl;
	sleep(1); 	
																							
	return manager->threadInitializer();
}

Manager*
Manager::GetInstance()
{	
	printf("Manager GetInstance\n");
	if(!mpInstance)
	{
		mpInstance = new Manager();
	}
		sleep(1);
	return mpInstance;
}

bool
Manager::threadInitializer()
{	
	 cout<<"In threadInitializer"<<endl;
	 sleep(1);
	 
	 pthread_create(&mThreadId,NULL,&Manager::Run,0);
	 
	 cout<<"Done with thread creation"<<endl;
	 sleep(1);

}
						
bool
Manager::socketInitialize()
{	
	cout<<"In server socket function"<<endl;
	sleep(1);
	int reuse_addr = 1;
	struct sockaddr_in serv_addr,client_addr;	

	mSock = socket(AF_INET, SOCK_STREAM, 0);
	memset(&serv_addr, '0', sizeof(serv_addr));
	
	cout<<"setSockopt Initialize"<<endl;
	sleep(1);

	setsockopt(mSock,SOL_SOCKET, SO_REUSEADDR,(void*)(&reuse_addr),sizeof(reuse_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(8888);

	cout<<"bind Initialize"<<endl;
	sleep(1);

	bind(mSock, (struct sockaddr *)&serv_addr,sizeof(serv_addr)); 

	cout<<"listen Initialize"<<endl;
	sleep(1);
		
	listen(mSock, 3);

	cout<<"accept Initialize"<<endl;
	sleep(1);
        
	int c = sizeof(client_addr);
	if ((mNewSocket = accept(mSock, (struct sockaddr *)&client_addr,(socklen_t*)&c))<0) 
	   	{ 
			cout<<"connection failed"<<endl;
			return false;
		}
		else
		{
			cout<<"Connection accepted\n"<<endl;
			return true;
		}
}

int
Manager::readFromSocket(char* buffer)
{
			const char* hello = "command received\n";
			cout<<"In readFromSocket"<<endl;
			sleep(1);
		 	
			//memset(buffer,'0',sizeof(buffer));
		    mReadSize = read(mNewSocket,buffer,1024);
		    //send(mNewSocket,hello,sizeof(hello),0);
		    printf("read_size %d and buffer is %s\n",mReadSize,buffer);	
		    return mReadSize;
			/*if(mReadSize == -1)
				return NULL;
				else*/
				//return buffer;		
		
}

void*
Manager::Run(void *arg)
{
	char* buffer;
	buffer = (char*)malloc(1024*(sizeof(char)));
	cout<<"In run Function\n"<<endl;
	sleep(1);
		
	Manager *manager = manager->GetInstance();
	if(manager->socketInitialize())
	{	
		cout<<"SocketInitialize is done"<<endl;
		sleep(1);
		int choice,count = 0,n;
		while(!manager->getIsFinalized())
			{	
				cout<<"In run getisFinalized loop"<<endl;
				sleep(1);
			
				memset(buffer,0,sizeof(buffer));										
				int ret_val = manager->readFromSocket(buffer);
				cout<<"buffer is "<<buffer<<endl;
				sleep(1);
				if (ret_val > 0)
				{
					cout<<"In if else loop"<<endl;
					sleep(1);
					if(strncmp(buffer,"exit",4)== 0)
				 	{
				 		cout << "Inside the exit compare"<<endl;
						for(int i=0;i<4;i++)
						{
							manager->getWorker(i)->setIsFinalized(true);				
						}
						
						break;
				 	}
					
					cout<<"Buffer is assigned"<<endl;
					sleep(1);
					n = count%4;
					manager->getWorker(n)->addToQueue(buffer,n);
					cout<<"addToQueue is done"<<endl;
					sleep(1);				
					count++;
				}
					//manager->getWorker(n)->Run(NULL);

		}		
	}
	printf("Run ends\n");
	sleep(1);
}
void Manager::Finalize()
{
		Manager* manager = manager->GetInstance();
		for(int i=0;i<4;i++)
		{
			manager->getWorker(i)->Finalize();				
		}
		manager->setIsFinalized(true);
		pthread_join(manager->getThreadId(), NULL);
		close(manager->mSock);
		close(manager->mNewSocket);
			
}
