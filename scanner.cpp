#include "scanner.hpp"
#include <fstream>


Scanner::Scanner(std::string fileName) {
    file.open(fileName);
    if(!file){
        std::cerr <<"Error: file not found.";
        exit(1);
    } 
    line = 1;
    currentChar = file.get();
    nextChar = file.get();
    isEOF = false;
}

char Scanner::nextToken() {
    if(isEOF) {
        return EOF;
    }
    
}