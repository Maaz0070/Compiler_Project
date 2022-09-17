#include "parseTree.hpp"
#include "scanner.hpp"

class Parser {
private:
    Scanner scanner;
public:
    Parser();
    Parser(std::string filename="masterTestCase.txt");
    ~Parser();
    parseTree *parseProgram();
    parseTree *parseStatement();
    // parseTree *parseAssignmentStatement();
    parseTree *parseCompoundStatement();
    // parseTree parseRepeatStatement();
    // parseTree parseWriteStatement();
    // parseTree parseWritelnStatement();
    // parseTree parseExpression();
    // parseTree parseSimpleExpression();
    // parseTree parseTerm();
    // parseTree parseFactor();
    // parseTree parseVariable();
    // parseTree parseIntegerConstant();
    // parseTree parseRealConstant();
    // parseTree parseStringConstant();
};
