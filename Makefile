CC=g++
output: main.o scanner.o parser.o Node.o
	$(CC) -g main.o scanner.o parser.o Node.o -o output

main.o: main.cpp
	$(CC) -g -c -std=c++17 main.cpp

scanner.o: scanner.cpp scanner.hpp
	$(CC) -g -c -std=c++17 scanner.cpp

parser.o: parser.cpp parser.hpp
	$(CC) -g -c -std=c++17 parser.cpp

Node.o: Node.cpp Node.hpp
	$(CC) -g -c -std=c++17 Node.cpp

clean:
	rm *.o output