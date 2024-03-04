CC = clang++
CFLAGS =
VERSION = c++20

mysh: src/shell.cpp src/interpreter.cpp src/shellmemory.cpp
	$(CC) $(CFLAGS) -c -std=$(VERSION) src/helper.cpp -o target/helper.o
	$(CC) $(CFLAGS) -c -std=$(VERSION) src/shell.cpp -o target/shell.o
	$(CC) $(CFLAGS) -c -std=$(VERSION) src/interpreter.cpp -o target/interpreter.o
	$(CC) $(CFLAGS) -c -std=$(VERSION) src/shellmemory.cpp -o target/shellmemory.o
	$(CC) $(CFLAGS) -std=$(VERSION) target/helper.o target/shell.o target/interpreter.o target/shellmemory.o -o target/mysh

clean:
	rm target/mysh target/*.o
