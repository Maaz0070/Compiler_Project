CC=g++
output: main.o scanner.o parser.o Node.o
	$(CC) -g main.o scanner.o parser.o Node.o -o output

main.o: main.cpp
	$(CC) -g -c -std=c++17 main.cpp

scanner.o: ./scanner/scanner.cpp ./scanner/scanner.hpp
	$(CC) -g -c -std=c++17 ./scanner/scanner.cpp

parser.o: ./parser/parser.cpp ./parser/parser.hpp
	$(CC) -g -c -std=c++17 ./parser/parser.cpp

Node.o: ./parser/Node.cpp ./parser/Node.hpp
	$(CC) -g -c -std=c++17 ./parser/Node.cpp

clean:
	rm *.o output