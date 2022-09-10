#include "symbolTable.hpp"

int symbolTable::hashFunction(std::string token) {
    int asc = 0;

    for(int i = 0; i < token.length(); i++) {
        asc = asc + token[i];
    }

    return asc % symbolTable::maxSize;
}

std::string symbolTable::look_up(std::string token) {
    int hash = hashFunction(token);
}