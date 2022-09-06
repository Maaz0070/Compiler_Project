
output: main.o scanner.o
	g++ -g main.o scanner.o -o output

main.o: main.cpp
	g++ -g -c -std=c++17 main.cpp

scanner.o: scanner.cpp scanner.hpp
	g++ -g -c -std=c++17 scanner.cpp

clean:
	rm *.o output