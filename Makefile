CC = gcc

mycc: mycc.o function.o
	$(CC) -o $@ mycc.o function.o
mycc.o: mycc.c mycc.h
	$(CC) -c $*.c
function.o: function.c mycc.h
	$(CC) -c $*.c