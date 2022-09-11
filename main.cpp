#include <iostream>
#include <fstream>
#include <iomanip>
#include "scanner.hpp"

// prints label and token
void printTok(Token tok, std::ostream& os) {
    if (tok.value == "EOF") return;
    if (tok.type == INVALID) {
        os << "TOKEN ERROR at line " << tok.line << ": " << " invalid string '"  << tok.value << "'" << std::endl;
        std::cout << "TOKEN ERROR at line " << tok.line << ": " << " invalid string '"  << tok.value << "'" << std::endl;
    }
    os << std::setw(20) << std::left << tok.label << std::setfill(' ') << ":   ";
    os << std::setw(60) << std::left << tok.value << std::setfill(' ') << std::endl;

    std::cout << std::setw(20) << std::left << tok.label << std::setfill(' ') << ":   ";
    std::cout << std::setw(60) << std::left << tok.value << std::setfill(' ');
}

//masterTestCase.txt
int main() {
    Scanner scanner("t.txt");
    // Scanner scanner("test-in.txt");
    std::ofstream os("test-out.txt");
    Token token = scanner.nextToken();
    while (!scanner.isEOF) {
        printTok(token, os);
        std::cout << std::endl;
        token = scanner.nextToken();
    }
    printTok(token, os);
    std::cout << std::endl;
    os.close();
    return 0;
}