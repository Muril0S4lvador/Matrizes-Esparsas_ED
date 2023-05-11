all: haha

haha:
	gcc -o main main.c sources/*.c

objects/node.o: headers/node.h sources/node.c
	gcc -o objects/node.o sources/node.c -c -Wall
    
objects/forwardlist.o: headers/forwardlist.h sources/forwardlist.c
	gcc -o objects/forwardlist.o sources/forwardlist.c -c -Wall

objects/matriz.o: headers/matriz.h sources/matriz.c
	gcc -o objects/matriz.o sources/matriz.c -c -Wall

compile: objects/matriz.o objects/forwardlist.o objects/node.o
	gcc -o main main.c objects/node.o objects/forwardlist.o objects/matriz.o -c -Wall

clean:
	rm -rf *.o *~ main
