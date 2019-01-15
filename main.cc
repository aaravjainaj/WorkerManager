#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<string.h>
#include "Manager.h"
#include "Worker.h"
using namespace std;

int main(int argc, char** argv)
{
	
	cout << "first step" << endl;
        sleep(1);
	
	Manager *manager = manager->GetInstance();

	manager->Initialize();

	cout << "Done with Initialize for Manager" << endl;
	sleep(1);
	manager->Finalize();

	printf("main end\n");
	return 0;
}
