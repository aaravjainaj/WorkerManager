#include<iostream>
#include<stdio.h>
#include<queue>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include "Worker.h"
#include "Manager.h"

using namespace std;
/*Worker::Worker() : mIsFinalized (false)
{
	cout<<"Worker Constructor"<<endl;
	sleep(1);
	for (int i = 0; i < 4; ++i)
	{
		mWorkers[i] = new Worker(i);
	}
}
*/
bool 
Worker::Initialize()
{

	printf("In Worker Initialize start\n");
	sleep(1);

	//mWorkerId = workerId;
	return threadInitialize();	
}

bool 
Worker::threadInitialize()
{
	mIsFinalized = false;
	pthread_create(&getWorkerThreadId(),NULL,&Worker::Run,(void*)this);
		
	cout<<"After pthread_Create"<<endl;
	sleep(1);

	printf("Worker Initialize end\n");
	sleep(1);

}

void Worker::addToQueue(char* buffer,int i)
{	
	printf("Worker Addtoqueue start\n");
	sleep(1);
	
	setMutexLock();
	
	cout<<"Before queue push calling"<<endl;
	sleep(1);

	pushInQueue(buffer);
	
	cout<<"After queue push calling"<<endl;
	sleep(1);
	
	printf("worker %d assigned %s",i%4,(char *)buffer);
	sleep(1);
	
	setMutexUnlock();
	
	printf("Worker Addtoqueue end\n");
	sleep(1);
}

void* Worker::Run(void* workerPtr)
{
    Worker* worker = (Worker*)workerPtr;
	while (!worker->getIsFinalized())
	{	
		//check if queue has anything to process
		// if so, print and pop from the queue
		worker->setMutexLock();
		if(worker->getQueueFront())
		{
			printf("process in queue is %s", worker->getQueueFront());
			worker->popInQueue();	
		}
		worker->setMutexUnlock();
		sleep(1);
		//else break;
	}
	
	cout << "Exiting from Worker Run for worker Id " << worker->getWorkerId() << endl;		
}

void Worker::Finalize()
{	
	//setMutexLock();
	cout << "Inside Worker Finalize " << endl;
	pthread_join(getWorkerThreadId(), NULL);
	//setMutexUnlock();
	printf("Worker finalize\n");
}

