CC=g++
output: main.o scanner.o parser.o
	$(CC) -g main.o scanner.o parser.o -o output

main.o: main.cpp
	$(CC) -g -c -std=c++17 main.cpp

scanner.o: scanner.cpp scanner.hpp
	$(CC) -g -c -std=c++17 scanner.cpp

parser.o: parser.cpp parser.hpp
	$(CC) -g -c -std=c++17 parser.cpp

clean:
	rm *.o output