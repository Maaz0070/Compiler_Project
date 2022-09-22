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
  Node *statement = parseSimpleStatement();
  if (statement != NULL) {
    return statement;
  }
  return parseStructuredStatement();
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
  Node *head = new Node(NodeType::ASSIGN, scanner.getCurTok().line);
  Node *var = new Node(NodeType::VARIABLE, scanner.getCurTok().line);
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
  scanner.nextToken();
  exp = parseExpression();
  exp->setLine(scanner.getCurTok().line);
  head->adopt(exp);
  // scanner.nextToken();
  
  // exp = parseExpression();
  if (exp == NULL) {
    return NULL;
  }

  return head;
}



Node *Parser::parseSimpleExpression() {
  Node *term = parseTerm();
  Node *term2;
  Node *exp;
  
  if (!term) {
    Node *sign = parseSign();
    if (sign) {
      term2 = parseTerm();
      if (term2) {
        sign->adopt(term2);
      }
      term = sign;
    }
  }
  
  Node *op = parseAddingOperator();
  if (op) {
    op->adopt(term);
    exp = parseSimpleExpression();
    if (exp) {
      op->adopt(exp);
    }
    return op;
  }

  return term;
}

Node *Parser::parseVariable() {
  if (scanner.getCurTok().label != "IDENTIFIER") {
    return NULL;
  }
  Node *head = new Node(NodeType::VARIABLE, scanner.getCurTok().line);
  head->setName(scanner.getCurTok().value);
  head->setLine(scanner.getCurTok().line);
  scanner.nextToken();
  return head;
}

Node *Parser::parseAddingOperator() {
  Node *head;
  if (scanner.getCurTok().label == "PLUSOP") {
    head = new Node(NodeType::ADD, scanner.getCurTok().line);
  } else if (scanner.getCurTok().label == "MINUSOP") {
    head = new Node(NodeType::SUBTRACT, scanner.getCurTok().line);
  } else if (scanner.getCurTok().label == "OR") {
    head = new Node(NodeType::OR, scanner.getCurTok().line);
  } else {
    return NULL;
  }
  
  head->setLine(scanner.getCurTok().line);
  scanner.nextToken();
  
  return head;
}

Node *Parser::parseUnsignedConstant() {
  if (scanner.getCurTok().label == "INTEGER") {
    Node *head = new Node(NodeType::INTEGER_CONSTANT, scanner.getCurTok().line);
    head->setValue(std::stoi(scanner.getCurTok().value));
    head->setLine(scanner.getCurTok().line);
    scanner.nextToken();
    return head;
  } else if (scanner.getCurTok().label == "IDENTIFIER") {
    Node *head = new Node(NodeType::VARIABLE, scanner.getCurTok().line);
    head->setName(scanner.getCurTok().value);
    head->setLine(scanner.getCurTok().line);
    scanner.nextToken();
    return head;
  } else if (scanner.getCurTok().label == "STRING") {
    Node *head = new Node(NodeType::STRING_CONSTANT, scanner.getCurTok().line);
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
    Node *head = new Node(NodeType::MULTIPLY, scanner.getCurTok().line);
    head->setLine(scanner.getCurTok().line);
    scanner.nextToken();
    return head;
  } else if (scanner.getCurTok().label == "DIVOP") {
    Node *head = new Node(NodeType::DIVIDE, scanner.getCurTok().line);
    head->setLine(scanner.getCurTok().line);
    scanner.nextToken();
    return head;
  } else {
    return NULL;
  }
}

Node *Parser::parseSign() {
  if (scanner.getCurTok().label == "PLUS") {
    Node *head = new Node(NodeType::POS, scanner.getCurTok().line);
    head->setLine(scanner.getCurTok().line);
    scanner.nextToken();
    return head;
  } else if (scanner.getCurTok().label == "MINUS") {
    Node *head = new Node(NodeType::NEGATE, scanner.getCurTok().line);
    head->setLine(scanner.getCurTok().line);
    scanner.nextToken();
    return head;
  } else {
    return NULL;
  }
}

Node *Parser::parseElementList() {
  Node *head = new Node(NodeType::LIST, scanner.getCurTok().line);
  Node *exp = parseExpression();
  if (exp) {
    head->adopt(exp);
    while (scanner.getCurTok().label == "COMMA") {
      scanner.nextToken();
      exp = parseExpression();
      if (exp) {
        head->adopt(exp);
      } else {
        return NULL;
      }
    }
    return head;
  }
  return NULL;
}

Node *Parser::parseElement() {
  Node *node = parseExpression();
  if (scanner.getCurTok().label == "DOTDOT") {
    scanner.nextToken();
    Node *node2 = parseExpression();
    if (node2) {
      Node *head = new Node(NodeType::DOTDOT, scanner.getCurTok().line);
      head->adopt(node);
      head->adopt(node2);
      return head;
    }
  }
  return NULL;
}

Node *Parser::parseEmpty() {
  return new Node(NodeType::EMPTY, scanner.getCurTok().line);
}

Node *Parser::parseTerm() {
  Node *node = parseFactor();
  if (node) {
    return node;
  }
  node = parseTerm();
  if (node) {
    Node *op = parseMultiplyingOperator();
    if (op) {
      Node *factor = parseFactor();
      if (factor) {
        op->adopt(node);
        op->adopt(factor);
        return op;
      }
    }
  }
  return NULL;
}

Node *Parser::parseFactor() {
  std::string l = scanner.getCurTok().label;
  Node *var = parseVariable();
  if (var) {
    return var;
  }
  Node *constNode = parseUnsignedConstant();
  if (constNode) {
    return constNode;
  }
  if (scanner.getCurTok().label == "LPAREN") {
    scanner.nextToken();
    Node *exp = parseExpression();
    if (exp) {
      if (scanner.getCurTok().label == "RPAREN") {
        scanner.nextToken();
        return exp;
      }
    }
  }
  Node *exp2 = parseExpression();
  if (exp2) {
      return exp2;
  }
  if (scanner.getCurTok().label == "NOT") {
    int notLine = scanner.getCurTok().line;
    scanner.nextToken();
    Node *factor = parseFactor();
    if (factor) {
      Node *head = new Node(NodeType::NOT, notLine);
      head->adopt(factor);
      return head;
    }
  }
  return NULL;
}

Node *Parser::parseString() {
  if (scanner.getCurTok().label != "STRING") {
    return NULL;
  }
  Node *head = new Node(NodeType::STRING_CONSTANT, scanner.getCurTok().line);
  head->setName(scanner.getCurTok().value);
  head->setLine(scanner.getCurTok().line);
  scanner.nextToken();
  return head;
}

Node *Parser::parseExpression() {
  Node *node = parseSimpleExpression();
  if (node == NULL) {
    return NULL;
  }
  Node *op = parseRelationalOperator();
  if (op != NULL) {
    Node *tmp = parseSimpleExpression();
    if (tmp == NULL) {
      return NULL;
    }
    op->adopt(node);
    op->adopt(tmp);
    return op;
  }
  return node;
}



// MULTIPLY, DIVIDE, EQ, LT,
// = | <> | < | <= | >= | > | in
Node *Parser::parseRelationalOperator() {
  std::string l = scanner.getCurTok().label;
  if (l != "EQUAL" && l != "NE" && l != "LT" && l != "LTEQ" && l != "GT" && l != "GTEQ") {
    if (scanner.getCurTok().value != "in") {
      return NULL;
    }
  }
  Node *head;
  if (l == "EQUAL") {
    head = new Node(NodeType::EQ, scanner.getCurTok().line);
  } else if (l == "NE") {
    head = new Node(NodeType::NE, scanner.getCurTok().line);
  } else if (l == "LT") {
    head = new Node(NodeType::LT, scanner.getCurTok().line);
  } else if (l == "LTEQ") {
    head = new Node(NodeType::LTEQ, scanner.getCurTok().line);
  } else if (l == "GT") {
    head = new Node(NodeType::GT, scanner.getCurTok().line);
  } else if (l == "GTEQ") {
    head = new Node(NodeType::GTEQ, scanner.getCurTok().line);
  } else if (scanner.getCurTok().value == "in") {
    head = new Node(NodeType::IN, scanner.getCurTok().line);
  }
  head->setLine(scanner.getCurTok().line);
  scanner.nextToken();
  return head;
}

Node *Parser::parseWriteStatement() {
  if (scanner.getCurTok().label != "WRITE") {
        return NULL;
    }
    Node *head = new Node(NodeType::WRITE, scanner.getCurTok().line);
    Node *exp;
    scanner.nextToken();
    if (scanner.getCurTok().label != "LPAREN") {
        return NULL;
    }

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

Node *Parser::parseWritelnStatement() {
    if (scanner.getCurTok().label != "WRITELN") {
        return NULL;
    }
    Node *head = new Node(NodeType::WRITELN, scanner.getCurTok().line);
    Node *exp;
    scanner.nextToken();
    if (scanner.getCurTok().label != "LPAREN") {
        return NULL;
    }

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
    scanner.nextToken();
    Node *head = new Node(NodeType::PROGRAM, scanner.getCurTok().line);
    head->setLine(scanner.getCurTok().line);
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
    if (scanner.getCurTok().label != "PERIOD")
        return NULL;
    return head;
}

Node *Parser::parseBlock() {
  Node *head;
  head = parseCompoundStatement();
  return head;
}

Node *Parser::parseCompoundStatement() {
  Node *head = new Node(NodeType::COMPOUND, scanner.getCurTok().line);
  head->setLine(scanner.getCurTok().line);
  if (scanner.getCurTok().label != "BEGIN")
    return NULL;
  scanner.nextToken();
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
  scanner.nextToken();
  return head;
}

Node *Parser::parseGoToStatement() {
    Node *head = new Node(NodeType::GOTO, scanner.getCurTok().line);
    return head;
}

Node *Parser::parseStructuredStatement() {
  Node *node;
  node = parseCompoundStatement();
  if (node != NULL)
    return node;
  node = parseConditionalStatement();
  if (node != NULL)
    return node;
  node = parseRepetitiveStatement();
  if (node != NULL)
    return node;
  return NULL;
  // node = parseWithStatement();
  // return node;
}

Node *Parser::parseRepetitiveStatement() {
  // Node *wh = parseWhileStatement();
  // if (wh != NULL)
  //   return wh;
  Node *re = parseRepeatStatement();
    return re;
  Node *fr = parseForStatement();
  if (fr != NULL)
    return fr;
}

Node *Parser::parseForStatement() {
    if (scanner.getCurTok().label != "FOR") {
        return NULL;
    }

}
 
Node *Parser::parseRepeatStatement() {
  Node *head = new Node(NodeType::LOOP, scanner.getCurTok().line);
  if (scanner.getCurTok().label != "REPEAT")
    return NULL;
  scanner.nextToken();
  do {
    Node *st = parseStatement();
    if (st == NULL)
      return NULL;
    head->adopt(st);
    if (scanner.getCurTok().label == "SEMICOLON")
      scanner.nextToken();
  } while (scanner.getCurTok().label != "UNTIL");
  scanner.nextToken();
  Node *unt = new Node(NodeType::TEST, scanner.getCurTok().line);
  Node *exp = parseExpression();
  if (exp == NULL)
    return NULL;
  unt->adopt(exp);
  head->adopt(unt);
  return head;
}

Node *Parser::parseConditionalStatement() {
  Node *ifnode = parseIfStatement();
  if (ifnode != NULL)
    return ifnode;
  Node *casenode = parseCaseStatement();
  if (casenode != NULL)
    return casenode;
  return NULL;
}

Node *Parser::parseIfStatement() {
  Node *head = new Node(NodeType::IF, scanner.getCurTok().line);
  if (scanner.getCurTok().label != "IF")
    return NULL;
  scanner.nextToken();
  Node *exp = parseExpression();
  Node *condNode = new Node(NodeType::COND, scanner.getCurTok().line);
  condNode->adopt(exp);
  head->adopt(condNode);
  if (exp == NULL)
    return NULL;
  if (scanner.getCurTok().label != "THEN")
    return NULL;
  scanner.nextToken();
  Node *stmnt = parseStatement();
  Node *thenNode = new Node(NodeType::THEN, scanner.getCurTok().line);
  thenNode->adopt(stmnt);
  head->adopt(thenNode);
  if (stmnt == NULL)
    return NULL;
  if (scanner.getCurTok().label == "ELSE") {
    Node *elsestmnt = parseStatement();
    if (elsestmnt == NULL)
      return NULL;
    Node *elseNode = new Node(NodeType::ELSE, scanner.getCurTok().line);
    elseNode->adopt(elsestmnt);
    head->adopt(elseNode);
  }
  return head;
}

Node *Parser::parseCaseStatement() {
  Node *head = new Node(NodeType::CASE, scanner.getCurTok().line);
  if (scanner.getCurTok().label != "CASE")
    return NULL;
  scanner.nextToken();
  Node *exp = parseExpression();
  if (exp == NULL)
    return NULL;
  head->adopt(exp);
  if (scanner.getCurTok().label != "OF")
    return NULL;
  scanner.nextToken();
  do {
    Node *caselistElem = parseCaseListElement();
    if (caselistElem == NULL)
      return NULL;
    head->adopt(caselistElem);
  } while (scanner.getCurTok().label == "SEMICOLON");
  if (scanner.getCurTok().label != "END")
    return NULL;
  return head;
}

Node *Parser::parseCaseListElement() {
  Node *head = new Node(NodeType::CASEELEM, scanner.getCurTok().line);
  Node *cll = parseCaseLabelList();
  if (cll == NULL)
    return NULL;
  head->adopt(cll);
  if (scanner.getCurTok().label != "COLON")
    return NULL;
  scanner.nextToken();
  Node *stmnt = parseStatement();
  if (stmnt == NULL)
    return NULL;
  head->adopt(stmnt);
  return head;
}

Node *Parser::parseCaseLabelList() {
  Node *node = new Node(NodeType::LIST, scanner.getCurTok().line);
  Node *label = parseCaseLabel();
  do {
    if (label == NULL)
    return NULL;
    node->adopt(label);
  } while (scanner.getCurTok().label == "COMMA");
  return node;
}

Node *Parser::parseCaseLabel() {
  return parseConstant();
}

Node *Parser::parseUnsignedNumber() {
  Node *node = parseUnsignedInteger();
  if (node != NULL)
    return node;
  node = parseUnsignedReal();
  return node;
}

Node *Parser::parseUnsignedInteger() {
  Node *node = new Node(NodeType::INTEGER_CONSTANT, scanner.getCurTok().line);
  if (scanner.getCurTok().label != "INTEGER")
    return NULL;
  node->setLine(scanner.getCurTok().line);
  node->setValue(atof(scanner.getCurTok().value.c_str()));
  scanner.nextToken();
  return node;
}

Node *Parser::parseUnsignedReal() {
  return parseRealConstant();
}

Node *Parser::parseRealConstant() {
  if (scanner.getCurTok().label != "REAL")
    return NULL;
  Node *node = new Node(NodeType::REAL_CONSTANT, scanner.getCurTok().line);
  node->setLine(scanner.getCurTok().line);
  node->setValue(atof(scanner.getCurTok().value.c_str()));
  scanner.nextToken();
  return node;
}

Node *Parser::parseConstant() {
  Node *num = parseUnsignedNumber();
  if (num != NULL)
    return num;
  Node *sign = parseSign();
  if (sign) {
    num = parseUnsignedNumber();
    if (num == NULL)
      return NULL;
    sign->adopt(num);
    return sign;
  }
  // Node *ci = parseConstantIdentifier();
  // if (ci != NULL)
  //   return ci;
  // sign = parseSign();
  // if (sign) {
  //   num = parseConstantIdentifier();
  //   if (num == NULL)
  //     return NULL;
  //   sign->adopt(num);
  //   return sign;
  // }
  Node *str = parseString();
  if (str != NULL)
    return str;
  return NULL;  
}

void Parser::outputTree(Node *node, int indentLevel) {
    std::string prefix = "";
    if (node == NULL) {
        return;
    }

    for (int i = 0; i < indentLevel; i++) {
        prefix += "   ";
    }

    if (node->getType() == NodeType::VARIABLE) {
      std::cout << prefix << "<" << node->getTypeString(); 
      std::cout << " line=" << node->getLine();
      std::cout << " name=" << node->getName() << "/>" << std::endl;
      return;
    }
    if (node->getType() == NodeType::STRING_CONSTANT) {
      std::cout << prefix << "<" << node->getTypeString(); 
      std::cout << " line=" << node->getLine();
      std::cout << " value=" << node->getName() << "/>" << std::endl;
      return;
    }
    if (node->getType() == NodeType::INTEGER_CONSTANT) {
      std::cout << prefix << "<" << node->getTypeString(); 
      std::cout << " line=" << node->getLine();
      std::cout << " value=" << node->getValue() << "/>" << std::endl;
      return;
    }
    if (node->getType() == NodeType::REAL_CONSTANT) {
      std::cout << prefix << "<" << node->getTypeString(); 
      std::cout << " line=" << node->getLine();
      std::cout << " name= " << node->getValue() << "/>" << std::endl;
      return;
    }

    if (node->getChildren().size() == 0) {
      std::cout << prefix << "<" << node->getTypeString() << " line=" << node->getLine() << "/>" << std::endl;
      return;
    }

    std::cout << prefix << "<"  << node->getTypeString() << " line=" << node->getLine() << ">" << std::endl;
    for (int i = 0; i < node->getChildren().size(); i++) {
        outputTree(node->getChildren()[i], indentLevel + 1);
    }
    std::cout << prefix << "<" << node->getTypeString() << "/>" << std::endl;
}
