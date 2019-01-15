cflags = -o 
cc = g++

main.o: main.cc Manager.h Worker.h
	cc -c main.cc
Manager.o: Manager.cc Manager.h Worker.h
	   cc -c Manager.cc
Worker.o: Worker.cc Manager.h Worker.h
	  cc -c Worker.cc
workermanager.a: main.o Manager.o 
		ar rs workermanager.a main.o Manager.o
workermanager: workermanager.a main.o
		cc -o workermanager -I. workermanager.a Worker.o -lpthread
clean: 
	-rm -f *.o core *.core
	
