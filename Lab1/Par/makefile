PROG = lab1
CFLAGS = -g -fPIC -m64 -Wall -std=gnu99
LFLAGS= -fPIC -m64 -Wall
CC = mpicc

all: $(PROG)

clean:
	-rm -f *.o core

lab1: lab1.c 
	$(CC) $(CFLAGS) lab1.c -o lab1.o