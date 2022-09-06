CC=gcc
output: main.o scanner.o
	$(CC) -g main.o scanner.o -o output

main.o: main.cpp
	$(CC) -g -c -std=c++17 main.cpp

scanner.o: scanner.cpp scanner.hpp
	$(CC) -g -c -std=c++17 scanner.cpp

clean:
	rm *.o output