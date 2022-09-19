#include "Node.hpp"
#include "../scanner/scanner.hpp"

class Parser {
  private:
    Scanner scanner;
    Node *curNode;
  public:
    Parser();
    Parser(std::string filename="masterTestCase.txt");
    ~Parser();
    Node *parseProgram();
    Node *parseStatement();
    Node *parseStatementList();
    Node *parseAssignmentStatement();
    Node *parseCompoundStatement();
    // Node parseRepeatStatement();
    // Node parseWriteStatement();
    // Node parseWritelnStatement();
    Node *parseExpression();
    Node *parseSimpleExpression();
    Node *parseTerm();
    Node *parseFactor();
    // Node parseVariable();
    Node *parseIntegerConstant();
    // Node parseRealConstant();
    // Node parseStringConstant();

    void outputTree(Node *node, int indentLevel=0); 
};
