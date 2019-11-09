ifeq ($(DEBUG), true)
	CC = gcc -g
else
	CC = gcc
endif

all: randfile.o
	$(CC) -o program randfile.o

randfile.o: randfile.c randfile.h
	$(CC) -c randfile.c randfile.h

run:
	./program

clean:
	rm *.o
	rm *.exe
	rm random

memcheck:
	valgrind --leak-check=yes ./program
