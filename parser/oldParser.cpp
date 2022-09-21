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

Node *Parser::parseProgram() {
    Node *head = new Node(NodeType::PROGRAM);
    Node *tmp;
    Token tok = scanner.nextToken();
    int firstLine = tok.line;
    if (tok.label != "PROGRAM")
      return NULL;
    tmp = parseIdentifier();
    if (tmp == NULL)
        return NULL;
    tok = scanner.nextToken();
    if (tok.label != "SEMICOLON")
        return NULL;
    tmp = parseBlock();
    if (tmp == NULL)
        return NULL;
    head->adopt(tmp);
    head->setType(NodeType::PROGRAM);
    head->setLine(firstLine);
    tok = scanner.nextToken();
    if (tok.label != "PERIOD")
        return NULL;
    return head; 
}


Node *Parser::parseIdentifier() {
    Token tok = scanner.nextToken();
    if (tok.label != "IDENTIFIER")
        return NULL;
    Node *node = new Node(NodeType::VARIABLE);
    node->setName(tok.value);
    node->setLine(tok.line);
    return node;
}

Node *Parser::parseBlock() {
    Node *head = new Node(NodeType::COMPOUND); 
    Node *tmp;

    tmp = parseTypeDefinitionPart();
    if (tmp != NULL)
        head->adopt(tmp);
    
    if (head != NULL) 
        return head;
    return NULL; // all failed
}

Node *Parser::parseLabel() {
    return parseUnsignedInteger();
}

Node *Parser::parseUnsignedNumber() {
    Node *head = new Node(NodeType::INTEGER_CONSTANT);
    Token tok = scanner.nextToken();


    if (tok.label=="INTEGER") {
      head->setValue(std::stoi(tok.value));
      return head;
    } else if (tok.label == "REAL") {
      head->setType(NodeType::REAL_CONSTANT);
      head->setValue(std::stof(tok.value));
      return head;
    } 
    return NULL;
}

Node *Parser::parseUnsignedInteger() {
    return parseIntegerConstant();
}

Node *Parser::parseSign() {
    Node *head = new Node(NodeType::NEGATE);
    Token tok = scanner.nextToken();
    if (tok.label == "PLUS") {
        head->setType(NodeType::POS);
        return head;
    } else if (tok.label == "MINUS") {
        return head;
    }
    return NULL;
}

Node *Parser::parseConstantIdentifier() {
    return parseIdentifier();
}

Node *Parser::parseString() {
  Node *node = new Node(NodeType::STRING_CONSTANT);
  Token tok = scanner.nextToken();
  if (tok.label != "STRING")
    return NULL;
  node->setName(tok.value);
  return node;
}



Node *Parser::parseCompoundStatement() {
    std::cout << "parseCompoundStatement" << std::endl;
    Node *head = new Node(NodeType::COMPOUND);
    Node *tmp;
    Token tok = scanner.nextToken();
    head->setLine(tok.line);
    if (tok.label == "BEGIN") {
        do {
            tmp = parseStatement();
            head->adopt(tmp);
            tok = scanner.nextToken();
        } while (tok.label == "SEMICOLON");
        if (tok.label == "END") {
            return head;
        }
    }
    return NULL; // SYNTAX ERROR SOMEWHERE
}

Node *Parser::parseStatementList() {
  
}

Node *Parser::parseStatement() {
    Node *cur, *res;
    Token tok = scanner.nextToken();
    if (tok.label == "IDENTIFIER") {
        curNode = new Node(NodeType::VARIABLE);
        curNode->setName(tok.value);
        res = parseAssignmentStatement();
        return res;
    } else if (tok.label == "BEGIN") {
        return parseCompoundStatement();
    } 
    // else if (tok.label == "REPEAT") {
    //     return parseRepeatStatement();
    // } else if (tok.label == "WRITE") {
    //     parseWriteStatement();
    // } else if (tok.label == "WRITELN") {
    //     return parseWritelnStatement();
    // }
    return NULL; // SYNTAX ERROR SOMEWHERE
}

Node *Parser::parseStatement() {
    return parseUnlabelledStatement();
}

Node *Parser::parseLabel() {
    return parseUnsignedInteger();
}

Node *Parser::parseUnlabelledStatement() {
    if (accept("BEGIN") || accept("GOTO")) {
        return parseSimpleStatement();
    } else if (accept("BEGIN") || accept("IF") || accept("REPEAT") || accept("WITH")) {
        return parseStructuredStatement();
    }
    return NULL;
}

Node *Parser::parseSimpleStatement() {
    Node *tmp;
    Token tok = scanner.nextToken();
    if (tok.label == "IDENTIFIER") {
        tmp = parseAssignmentStatement();
        if (tmp!=NULL)
            return tmp;
    } else if (tok.label == "GOTO") {
        tmp = parseGoToStatement();
        if (tmp!=NULL)
            return tmp;
    } 
    tmp = parseEmptyStatement();
    return tmp;
}

Node *Parser::parseStructuredStatement() {
    Node *tmp = NULL;
    Token tok = scanner.nextToken();
    if (tok.label == "BEGIN") {
        tmp = parseCompoundStatement();
    } else if (tok.label == "IF" || tok.label == "CASE") {
        tmp = parseConditionalStatement();
    } else if (tok.label == "REPEAT") {
        tmp = parseRepeatStatement();
    } else if (tok.label == "WITH") {
        tmp = parseWithStatement();
    }
    return tmp;
}

Node *Parser::parseConditionalStatement() {
    if 
}

Node *Parser::parseGoToStatement() {
    Node *head = new Node(NodeType::GOTO);
    return head;
}

Node *Parser::parseEmptyStatement() {

}

Node *Parser::parseAssignmentStatement() {  
    Node *head = new Node(NodeType::ASSIGN);
    Token tok = scanner.nextToken();
    
    head->adopt(curNode);

    // example: alpha := -88;
    if (tok.label != "ASSIGN") {
        return NULL; // SYNTAX ERROR
    }

    head->adopt(parseExpression());
    return head;
}

Node *Parser::parseExpression() {
    return parseSimpleExpression();
}

Node *Parser::parseSimpleExpression() {
  Node *head;
  head = parseTerm();
  if (head != NULL) {
    return head;
  } else if (scanner.nextToken().label == "MINUS") {
    head = parseTerm();
    if (head != NULL) {
      return head;
    } 
  } else {
    head = parseSimpleExpression();
    if (scanner.nextToken().label != "PLUS") {
      return NULL; // SYNTAX ERROR
    }
  }
  //<simple expression> <adding operator> <term>  
  return NULL;
}

Node *Parser::parseTerm() {
  Node *head;
  head = parseFactor();
  if (head != NULL) {
    return head;
  }
  return NULL;
}

Node *Parser::parseFactor() {
  Node *head;
  head = parseIntegerConstant();
  if (head != NULL) {
    return head;
  }
  return NULL;
}


Node *Parser::parseIntegerConstant() {
  Node *head = new Node(NodeType::INTEGER_CONSTANT);
  Token tok = scanner.nextToken();
  if (tok.label=="INTEGER") {
    head->setValue(std::stoi(tok.value));
    return head;
  } 
  return NULL;
}

// Node *Node::parseStatement(std::string exp) {
//     std::vector<char*> list;
//     for(int i = 0; exp.length(); i++) {
//         list.push_back(&exp[i]);
//     }
//     std::stack<Node*> stack;
//     Node *head = new Node("");
//     std::vector<std::string> vect{"+", "-", "*", "/"};
//     std::vector<std::string> vect1{"+", "-", "*", "/", ")"};

//     stack.push(head);
//     Node *curr = head;
    
//     for(int i = 0; i < list.size(); i++) {
//         std::string currChar(list[i]);
//         if(list[i] == "(") {
//             curr->insertLeft("");
//             stack.push(curr);
//             curr = curr->getLeftChild();
//         }
//         else if(find(vect.begin(), vect.end(), currChar) != vect.end()) {
//             curr->setId(list[i]);
//             curr->insertRight("");
//             stack.push(curr);
//             curr = curr->getRightChild();
//         }
//         else if(list[i] == ")") {
//             curr = stack.top();
//             stack.pop();
//         }
//         else if(find(vect1.begin(), vect1.end(), list[i]) == vect1.end()) {
//             curr->setId(list[i]);
//             Node *root = stack.top();
//             stack.pop();
//             curr = root;
//         }
//     }
//     return head;
// }

void printTag() {

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