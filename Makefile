CC=clang
CFLAGS=-g -O0
SHELL=zsh
DIFF=colordiff

main: file.o lexer.o operand.o parser.o statement.o token.o utils.o main.o
	$(CC) $(CFLAGS) -o main *.o

clean:
	rm -f *.o main

test: main
	$(SHELL) -c 'colordiff -ub fixtures/expected.stdout <(./main)'
