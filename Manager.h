#ifndef _MANAGER_H
#define _MANAGER_H
#include "Worker.h"
#include<queue>
#include<iostream>
using namespace std;
class Manager
{
	public:
		virtual ~Manager() {};
		static Manager* GetInstance();
		static bool Initialize();
		static void Finalize();

		pthread_t& getThreadId() { return mThreadId; }
		bool getIsFinalized() { return mIsFinalized; }
		Worker* getWorker(int32_t i) { if (i > 3) return NULL; return mWorkers[i]; }
		
		void setIsFinalized(bool val) { mIsFinalized = val; }
		static void* Run(void *arg);
		

	private:
		Worker* mWorkers[4];
		int mReadSize;
		int mSock, mNewSocket;
		pthread_t mThreadId;
		static Manager* mpInstance;
		bool mIsFinalized;
		

		Manager();
		bool threadInitializer();
		bool socketInitialize();
		int readFromSocket(char*);
		
		
};

#endif
