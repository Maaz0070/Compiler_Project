#include "parser.hpp"
#include <iostream>

Parser::Parser() {
  scanner = Scanner("masterTestCase.txt");
}

Parser::Parser(std::string filename) {
  scanner = Scanner(filename);
}

Parser::~Parser() {

}

bool Parser::accept(std::string label) {
  Token tok = scanner.getCurTok();
  if (tok.label == label) {
    scanner.nextToken();
    return true;
  }
  return false;
}

bool Parser::expect(std::string label) {
  if (accept(label)) {
    return true;
  }
  std::cout << "ERROR: Expected stead." << std::endl;
  return false;
}

Node *Parser::parseStatement() {
  return parseUnlabelledStatement();
}

Node *Parser::parseUnlabelledStatement() {
  return parseSimpleStatement();
}

Node *Parser::parseSimpleStatement() {
  if (scanner.getCurTok().label == "WRITE") {
    return parseWriteStatement();
  } else if (scanner.getCurTok().label == "WRITELN") {
    return parseWritelnStatement();
  } else if (scanner.getCurTok().label == "IDENTIFIER") {
    return parseAssignmentStatement();
  } else if (scanner.getCurTok().label == "GOTO") {
    return parseGoToStatement();
  } else {
    return NULL;
  }
}

Node *Parser::parseAssignmentStatement() {
  if (scanner.getCurTok().label != "IDENTIFIER") {
    return NULL;
  }
  Node *head = new Node(NodeType::ASSIGN);
  Node *var = new Node(NodeType::VARIABLE);
  Node *exp;

  var->setName(scanner.getCurTok().value);
  var->setLine(scanner.getCurTok().line);
  head->adopt(var);
  scanner.nextToken();

  if (scanner.getCurTok().label != "ASSIGN") {
    return NULL;
  }
  // while (scanner.getCurTok().label != "SEMICOLON") {
  //   exp = parseExpression();
  //   exp->setLine(scanner.getCurTok().line);
  //   if (exp == NULL) {
  //     return NULL;
  //   }
  //   scanner.nextToken();
  //   head->adopt(exp);
  // }
  exp = parseExpression();
  exp->setLine(scanner.getCurTok().line);
  head->adopt(exp);
  scanner.nextToken();
  // scanner.nextToken();
  
  // exp = parseExpression();
  if (exp == NULL) {
    return NULL;
  }

  return head;
}

Node *Parser::parseSimpleExpression() {
  Node *head, *tmp, *tmp2, *tmp3;
  head = parseTerm(); 
  if (head != NULL) {
    return head;
  }
  head = parseSign();
  tmp = parseTerm();
  if (head != NULL && tmp != NULL) {
    head->adopt(tmp);
    return head;
  }
  head = new Node(NodeType::ADD);
  tmp = parseSimpleExpression();
  tmp2 = parseAddingOperator();
  tmp3 = parseSimpleExpression();
  head->adopt(tmp);
  head->adopt(tmp2);
  head->adopt(tmp3);
  if (head==NULL || tmp==NULL || tmp2==NULL || tmp3==NULL) {
    return NULL;
  }
  return head;
}

Node *Parser::parseVariable() {
  if (scanner.getCurTok().label != "IDENTIFIER") {
    return NULL;
  }
  Node *head = new Node(NodeType::VARIABLE);
  head->setName(scanner.getCurTok().value);
  head->setLine(scanner.getCurTok().line);
  scanner.nextToken();
  return head;
}

Node *Parser::parseAddingOperator() {
  if (scanner.getCurTok().label == "PLUS") {
    Node *head = new Node(NodeType::ADD);
    head->setLine(scanner.getCurTok().line);
    scanner.nextToken();
    return head;
  } else if (scanner.getCurTok().label == "MINUS") {
    Node *head = new Node(NodeType::SUBTRACT);
    head->setLine(scanner.getCurTok().line);
    scanner.nextToken();
    return head;
  } else {
    return NULL;
  }
}

Node *Parser::parseUnsignedConstant() {
  if (scanner.getCurTok().label == "INTEGER_CONSTANT") {
    Node *head = new Node(NodeType::INTEGER_CONSTANT);
    head->setValue(std::stoi(scanner.getCurTok().value));
    head->setLine(scanner.getCurTok().line);
    scanner.nextToken();
    return head;
  } else if (scanner.getCurTok().label == "IDENTIFIER") {
    Node *head = new Node(NodeType::VARIABLE);
    head->setName(scanner.getCurTok().value);
    head->setLine(scanner.getCurTok().line);
    scanner.nextToken();
    return head;
  } else {
    return NULL;
  }
}

Node *Parser::parseMultiplyingOperator() {
  if (scanner.getCurTok().label == "MULTOP") {
    Node *head = new Node(NodeType::MULTIPLY);
    head->setLine(scanner.getCurTok().line);
    scanner.nextToken();
    return head;
  } else if (scanner.getCurTok().label == "DIVOP") {
    Node *head = new Node(NodeType::DIVIDE);
    head->setLine(scanner.getCurTok().line);
    scanner.nextToken();
    return head;
  } else {
    return NULL;
  }
}

Node *Parser::parseSign() {
  if (scanner.getCurTok().label == "PLUS") {
    Node *head = new Node(NodeType::POS);
    head->setLine(scanner.getCurTok().line);
    scanner.nextToken();
    return head;
  } else if (scanner.getCurTok().label == "MINUS") {
    Node *head = new Node(NodeType::NEGATE);
    head->setLine(scanner.getCurTok().line);
    scanner.nextToken();
    return head;
  } else {
    return NULL;
  }
}

Node *Parser::parseTerm() {
  Node *head, *tmp, *tmp2, *tmp3;
  head = parseFactor();
  if (head != NULL) {
    return head;
  }
  head = new Node(NodeType::MULTIPLY);
  tmp = parseTerm();
  tmp2 = parseMultiplyingOperator();
  tmp3 = parseFactor();
  head->adopt(tmp);
  head->adopt(tmp2);
  head->adopt(tmp3);
  if (head==NULL || tmp==NULL || tmp2==NULL || tmp3==NULL) {
    return NULL;
  }
  return head;
}

Node *Parser::parseFactor() {
  if (scanner.getCurTok().label == "IDENTIFIER") {
    return parseVariable();
  } else if (scanner.getCurTok().label == "INTEGER") {
    return parseUnsignedConstant();
  } else if (scanner.getCurTok().label == "STRING") {
    return parseString();
  } else if (scanner.getCurTok().label == "LPAREN") {
    return parseExpression();
    if (scanner.getCurTok().label != "RPAREN") {
      scanner.nextToken();
      return NULL;
    }
  } else {
    return NULL;
  }
}

Node *Parser::parseString() {
  if (scanner.getCurTok().label != "STRING") {
    return NULL;
  }
  Node *head = new Node(NodeType::STRING_CONSTANT);
  head->setName(scanner.getCurTok().value);
  head->setLine(scanner.getCurTok().line);
  scanner.nextToken();
  return head;
}

Node *Parser::parseExpression() {
  return parseSimpleExpression();
}

Node *Parser::parseWriteStatement() {
}

Node *Parser::parseWritelnStatement() {
    if (scanner.getCurTok().label != "WRITELN") {
        return NULL;
    }
    Node *head = new Node(NodeType::WRITELN);
    Node *exp;
    scanner.nextToken();
    if (scanner.getCurTok().label != "LPAREN") {
        return NULL;
    }

    // do {
    //     scanner.nextToken();
    //     exp = parseExpression();
    //     if (exp != NULL) {
    //         head->adopt(exp);
    //     }
    //     if (scanner.nextToken().label == "COMMA") {
    //         scanner.nextToken();
    //     }
    // } while (scanner.getCurTok().label != "RPAREN");
    scanner.nextToken();
    exp = parseExpression();
    if (exp == NULL) {
        return NULL;
    }
    head->adopt(exp);
    if (scanner.getCurTok().label != "RPAREN") {
        return NULL;
    }
    scanner.nextToken();
    return head;
}

Node *Parser::parseProgram() {
    Node *head = new Node(NodeType::PROGRAM);
    scanner.nextToken();
    if (scanner.getCurTok().label != "PROGRAM")
      return NULL;
    if (scanner.nextToken().label != "IDENTIFIER")
        return NULL;
    if (scanner.nextToken().label != "SEMICOLON")
        return NULL;
    scanner.nextToken();
    Node *tmp = parseBlock();
    if (tmp == NULL)
        return NULL;
    head->adopt(tmp);
    head->setType(NodeType::PROGRAM);
    head->setLine(scanner.getCurTok().line);
    if (scanner.nextToken().label != "PERIOD")
        return NULL;
    return head;
}

Node *Parser::parseBlock() {
  Node *head;
  head = parseCompoundStatement();
  return head;
}

Node *Parser::parseCompoundStatement() {
  if (scanner.getCurTok().label != "BEGIN")
    return NULL;
  scanner.nextToken();
  Node *head = new Node(NodeType::COMPOUND);
  head->setLine(scanner.getCurTok().line);
  do {
    Node *tmp = parseStatement();
    if (tmp == NULL)
      return NULL;
    head->adopt(tmp);
    if (scanner.getCurTok().label == "SEMICOLON")
      scanner.nextToken();
  } while (scanner.getCurTok().label != "END");

  if (scanner.getCurTok().label != "END")
    return NULL;
  return head;
}

Node *Parser::parseGoToStatement() {
    Node *head = new Node(NodeType::GOTO);
    return head;
}


void Parser::outputTree(Node *node, int indentLevel) {
    std::string prefix = "";
    if (node == NULL) {
        return;
    }

    for (int i = 0; i < indentLevel; i++) {
        prefix += "  ";
    }

    if (node->getChildren().size() == 0) {
      std::cout << prefix << "<" << node->getTypeString() << "/>" << std::endl;
      return;
    }

    std::cout << prefix << "<" << node->getTypeString() << ">" << std::endl;
    for (int i = 0; i < node->getChildren().size(); i++) {
        outputTree(node->getChildren()[i], indentLevel + 1);
    }
    std::cout << prefix << "<" << node->getTypeString() << "/>" << std::endl;
}
