all: clean main

compile:
	gcc -g -o main main.c sources/*.c

objects/node.o: headers/node.h sources/node.c
	gcc -g -o objects/node.o sources/node.c -Wall

objects/forwardlist.o: headers/forwardlist.h sources/forwardlist.c
	gcc -g -o objects/forwardlist.o sources/forwardlist.c -Wall

objects/matriz.o: headers/matriz.h sources/matriz.c
	gcc -g -o objects/matriz.o sources/matriz.c -Wall

objects/main.o: headers/node.h headers/forwardlist.h headers/matriz.h
	gcc -g -o objects/main.o main.c -Wall

main: objects/node.o objects/forwardlist.o objects/matriz.o objects/main.o
	gcc -g -o main objects/main.o objects/node.o objects/forwardlist.o objects/matriz.o -Wall
	@echo
	@echo Programa compilado!
	@echo

run: main
	./main

val: main
	valgrind ./main

clean:
	rm -rf *.o *~ main
