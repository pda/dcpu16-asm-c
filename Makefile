build/main: $(OBJECTS) main.c
	clang $(wildcard build/*.o) main.c -o build/main
