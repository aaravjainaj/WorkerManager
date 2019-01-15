#ifndef WORKER_H
#define WORKER_H
#include<iostream>
#include<string.h>
#include<pthread.h>
#include<queue>
using namespace std;

class Worker
{
	
       	public:
	    Worker(int workerId) : mThreadId (workerId), mWorkerThreadId (0), mIsFinalized(false){};
	    ~Worker(){};
	    static void* Run(void *);
	    bool Initialize();
        void Finalize();
        void addToQueue(char *,int);
        void setIsFinalized(bool val) { mIsFinalized = val;}
        bool getIsFinalized() { return mIsFinalized; }
        char* getQueueFront(){return workerqueue.front();}
        void  pushInQueue(char* buffer){workerqueue.push(buffer);}
        void  popInQueue(){workerqueue.pop();}
        
        int getWorkerId() { return mThreadId; }
		//Worker* getWorker(int32_t i) { if (i > 3) return NULL; return mWorkers[i]; }
                                                                                              
	private:
		pthread_t mWorkerThreadId;
		int mThreadId;
		bool mIsFinalized;
		queue <char*> workerqueue;
		pthread_mutex_t worker_mutex;
		bool threadInitialize();
		pthread_t& getWorkerThreadId(){return mWorkerThreadId;}
        int setMutexLock(){return pthread_mutex_lock(&worker_mutex);}
        int setMutexUnlock(){return pthread_mutex_unlock(&worker_mutex);}
        //char* getWorkerQueue(){return  workerqueue.push();}
        //void popWorkerQueue(){ workerqueue.pop();}
        //void frontWorkerQueue(){workerqueue.front();}
		
};

/*
typedef struct Queue
{
        int capacity;
        int size;
        int front;
        int rear;
        char **elements;
} mDQueue;

Queue * createQueue(int maxElements)
{
        Queue *Q;
        Q = (Queue *)malloc(sizeof(Queue));
        Q->elements = (char**)malloc(sizeof(char*)*maxElements);
        Q->size = 0;
        Q->capacity = maxElements;
        Q->front = 0;
        Q->rear = -1;
        return Q;
}
*/
#endif
