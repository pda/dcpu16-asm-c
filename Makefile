CC=clang

main: utils.o main.c
	clang -o main *.o main.c

clean:
	rm -f *.o main
