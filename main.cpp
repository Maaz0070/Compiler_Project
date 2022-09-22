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
    os << tok.line << std::endl;

    std::cout << std::setw(20) << std::left << tok.label << std::setfill(' ') << ":   ";
    std::cout << std::setw(60) << std::left << tok.value << std::setfill(' ');
}

void testScanner(std::string filename="test-in.txt") {
    Scanner scanner(filename);
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
}

void testParser(std::string filename="test-in.txt") {
    Parser parser(filename);
    std::ofstream os("test-out.txt");
    Node *head = parser.parseProgram();

    os << "PARSER OUTPUT" << std::endl;
    std::cout << "PARSER OUTPUT" << std::endl;
    parser.outputTree(head, 0, os);
    parser.outputTree(head, 0);
    os << std::endl;
    std::cout << std::endl;

    os << "SYMBOL TABLE" << std::endl;
    std::cout << "SYMBOL TABLE" << std::endl;
    parser.outputSymbolTable(os);
    parser.outputSymbolTable();
    os << std::endl;
    std::cout << std::endl;
    os.close();
}

//masterTestCase.txt
int main(int argc, char *argv[]) {

    if (argc == 1) {
        testParser("test-in.txt");
    } else if (argc == 3 && std::string(argv[1]) == "-scan") {
        testScanner(std::string(argv[2]));
    } else if (argc == 3 && std::string(argv[1]) == "-parse") {
        testParser(std::string(argv[2]));
    } else {
        std::cout << "Usage: ./output -parse [filename] OR" << std::endl;
        std::cout << "./output -scan [filename]" << std::endl;
    }

    return 0;
}