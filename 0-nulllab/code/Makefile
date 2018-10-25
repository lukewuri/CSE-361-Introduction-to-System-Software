all:  lab0

CFLAGS = -g -Werror -Wall -O0

clean:
	rm -f lab0 *.o

input.o:  input.c
	gcc $(CFLAGS) -c input.c -o input.o

lab0.o:  lab0.c input.h
	gcc $(CFLAGS) -c lab0.c -o lab0.o

lab0:  lab0.o input.o
	gcc lab0.o input.o -o lab0
