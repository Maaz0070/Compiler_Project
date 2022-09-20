#include <iostream>
#include <fstream>
#include <iomanip>
#include "./scanner/scanner.hpp"
#include "./parser/parser.hpp"

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
    
    Parser parser("io/t.txt");
    Node *head = parser.parseProgram();

    parser.outputTree(head);

    return 0;
}