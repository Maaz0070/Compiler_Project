CC=g++
output: main.o scanner.o parser.o Node.o SymTab.o SymTabNode.o
	$(CC) -g main.o scanner.o parser.o Node.o SymTab.o SymTabNode.o -o output

main.o: main.cpp
	$(CC) -g -c -std=c++17 main.cpp

scanner.o: ./scanner/scanner.cpp ./scanner/scanner.hpp
	$(CC) -g -c -std=c++17 ./scanner/scanner.cpp

parser.o: ./parser/parser.cpp ./parser/parser.hpp
	$(CC) -g -c -std=c++17 ./parser/parser.cpp

Node.o: ./parser/Node.cpp ./parser/Node.hpp
	$(CC) -g -c -std=c++17 ./parser/Node.cpp

SymTab.o: ./parser/SymTab.cpp ./parser/SymTab.hpp
	$(CC) -g -c -std=c++17 ./parser/SymTab.cpp

SymTabNode.o: ./parser/SymTabNode.cpp ./parser/SymTabNode.hpp
	$(CC) -g -c -std=c++17 ./parser/SymTabNode.cpp

clean:
	rm *.o output