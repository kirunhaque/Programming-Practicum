waitinglist: interfaceFunctions.o listFunctions.o doFunctions.o
	gcc -o waitinglist interfaceFunctions.o listFunctions.o doFunctions.o

interfaceFunctions.o: interfaceFunctions.c waitinglist.h
	gcc -std=c99 -c interfaceFunctions.c

doFunctions.o: doFunctions.c waitinglist.h
	gcc -std=c99 -c doFunctions.c 

listFunctions.o: listFunctions.c waitinglist.h
	gcc -std=c99 -c listFunctions.c

