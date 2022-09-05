#include <iostream>
#include "scanner.hpp"

void printTok(Token tok) {
    std::cout << tok.value << "\t";
    if (tok.type == WORD) {
        std::cout << " WORD";
    } else if (tok.type == NUMBER) {
        std::cout << " NUMBER";
    } else if (tok.type == OPERATOR) {
        std::cout << " OPERATOR";
    } else if (tok.type == SPECIAL) {
        std::cout << " SPECIAL";
    } else if (tok.type == STRLITERAL) {
        std::cout << " STRLITERAL";
    } else {
        std::cout << " INVALID";
    }
}

int main() {
    Scanner scanner("P2.pas");
    Token token = scanner.nextToken();
    while (!scanner.isEOF) {
        printTok(token);
        std::cout << std::endl;
        token = scanner.nextToken();
    }
    printTok(token);
    std::cout << std::endl;
    return 0;
}