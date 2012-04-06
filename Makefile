CC=clang

main: file.o lexer.o parser.o token.o utils.o main.o
	clang -o main *.o

clean:
	rm -f *.o main
