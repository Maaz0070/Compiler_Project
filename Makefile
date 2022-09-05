
output: main.o scanner.o
	g++ main.o scanner.o -o output

main.o: main.cpp
	g++ -c -std=c++11 main.cpp

scanner.o: scanner.cpp scanner.hpp
	g++ -c -std=c++11 scanner.cpp

clean:
	rm *.o output