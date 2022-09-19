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

// Node *Parser::parseProgram() {
//     Node *head = new Node(NodeType::PROGRAM);
    
//     Token tok = scanner.nextToken();
//     if (tok.label == "PROGRAM") {
//         tok = scanner.nextToken();
//         if (tok.label == "IDENTIFIER") {
//           head->setName(tok.value);
//         } else {
//           return NULL; // SYNTAX ERROR
//         }
//         tok = scanner.nextToken();
//         if (tok.label != "LPAREN") {
//           return NULL; // SYNTAX ERROR
//         }
//         while (tok.label != "RPAREN") {
//           tok = scanner.nextToken();
//           if (tok.label != "IDENTIFIER") {
//             return NULL; // SYNTAX ERROR
//           }
//           tok = scanner.nextToken();
//           if (tok.label == "RPAREN") {
//             break;
//           } else if (tok.label != "COMMA") {
//             return NULL; // SYNTAX ERROR
//           }
//         }
//         if (tok.label == "SEMICOLON") {
//             head->adopt(parseCompoundStatement());
//             tok = scanner.nextToken();
//             if (tok.label == "DOT") {
//                 return head;
//             }
//         }
//     }

//     return NULL; // SYNTAX ERROR SOMEWHERE
// }

Node *Parser::parseCompoundStatement() {
    std::cout << "parseCompoundStatement" << std::endl;
    Node *head = new Node(NodeType::COMPOUND);
    Node *tmp;
    Token tok = scanner.nextToken();
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