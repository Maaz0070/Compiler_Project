#include <iostream>
#include <iomanip>
#include "scanner.hpp"

void printTok(Token tok) {
    std::cout << std::setw(60); 
    std::cout << std::left;
    std::cout << tok.value;
    std::cout << std::setfill(' ');
    std::cout << std::setw(20);
    if (tok.type == WORD) {
        std::cout << " WORD";
    } else if (tok.type == INTEGERS) {
        std::cout << " INTEGERS";
    } else if (tok.type == DECIMAL) {
        std::cout << " DECIMAL";
    } else if (tok.type == SPECIAL1) {
        std::cout << " SPECIAL1";
    } else if (tok.type == SPECIAL2) {
        std::cout << " SPECIAL2";
    } else if (tok.type == QUOTES) {
        std::cout << " QUOTES";
    } else {
        std::cout << " INVALID";
    }
    std::cout << std::setfill(' ');

    std::cout << std::setw(20);
    std::cout << std::left << tok.label;
}

//masterTestCase.txt
int main() {
    Scanner scanner("masterTestCase.txt");
    Token tokens[100];
    int i = 0;

    Token token = scanner.nextToken();
    int width = 60;
    std::cout << "Token" << std::setw(width) << std::setfill(' ') << "TokenType" << std::setw(20) << std::setfill(' ') << "Label" << std::endl;
    while (!scanner.isEOF) {
        printTok(token);
        tokens[i] = token;
        i++;
        std::cout << std::endl;
        token = scanner.nextToken();
    }
    printTok(token);
    std::cout << std::endl;
    return 0;
}