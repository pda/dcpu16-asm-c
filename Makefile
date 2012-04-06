CC=clang

main: file.o utils.o main.o
	clang -o main *.o

clean:
	rm -f *.o main
