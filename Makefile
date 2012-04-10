CC=clang
CFLAGS=-g -O0

main: file.o lexer.o parser.o token.o utils.o main.o
	$(CC) $(CFLAGS) -o main *.o

clean:
	rm -f *.o main
