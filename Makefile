CC = gcc

mycc: mycc.o tokenizer.o parser.o CodeGenerater.o
	$(CC) -o $@ mycc.o tokenizer.o parser.o CodeGenerater.o
mycc.o: mycc.c mycc.h
	$(CC) -c $*.c
tokenizer.o: tokenizer.c mycc.h
	$(CC) -c $*.c
parser.o: parser.c mycc.h
	$(CC) -c $*.c
CodeGenerater.o: CodeGenerater.c mycc.h
	$(CC) -c $*.c