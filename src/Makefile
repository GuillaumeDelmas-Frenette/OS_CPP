CC = clang++
CFLAGS =

mysh: src/shell.cpp src/interpreter.cpp src/shellmemory.cpp
	$(CC) $(CFLAGS) -c src/helper.cpp -o target/helper.o
	$(CC) $(CFLAGS) -c src/shell.cpp -o target/shell.o
	$(CC) $(CFLAGS) -c src/interpreter.cpp -o target/interpreter.o
	$(CC) $(CFLAGS) -c src/shellmemory.cpp -o target/shellmemory.o
	$(CC) $(CFLAGS) target/helper.o target/shell.o target/interpreter.o target/shellmemory.o -o target/mysh

clean:
	rm target/mysh target/*.o
