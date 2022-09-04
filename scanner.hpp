#include <string>
#include <iostream>
#include <fstream>


class Scanner {
    private:
        std::string fileName;
        std::ifstream file;
        int line;
        char currentChar;
        char nextChar;
        bool isEOF;
    
    public:
        Scanner(std::string fileName);
        char nextToken();
};