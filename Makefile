CC = gcc
CFLAGS=-std=c11 -g -static

kscc:kscc.c

clean:
	rm -f kscc *.o *~ tmp*

