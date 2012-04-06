CC=clang

main: main.c
	clang -o main main.c

clean:
	rm -f main
