#include <iostream>
#include <iomanip>
#include "scanner.hpp"

void printTok(Token tok) {
    std::cout << std::setw(60) << std::left << tok.value  << std::setfill(' ');
    std::cout << std::setw(20);
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
    std::cout << std::setfill(' ');

    std::cout << std::setw(20);
    std::cout << std::left << tok.label;
}

int main() {
    Scanner scanner("P2.pas");
    Token token = scanner.nextToken();
    int width = 60;
    std::cout << "Token" << std::setw(width) << std::setfill(' ') << "TokenType" << std::setw(20) << std::setfill(' ') << "Label" << std::endl;
    while (!scanner.isEOF) {
        printTok(token);
        std::cout << std::endl;
        token = scanner.nextToken();
    }
    printTok(token);
    std::cout << std::endl;
    return 0;
}