#include "parser.hpp"

Parser::Parser() {
  scanner = Scanner("masterTestCase.txt");
}

Parser::Parser(std::string filename) {
  scanner = Scanner(filename);
}

parseTree *Parser::parseProgram() {
    parseTree *head = new parseTree(NodeType::PROGRAM);
    
    Token tok = scanner.nextToken();
    if (tok.label == "PROGRAM") {
        tok = scanner.nextToken();
        if (tok.label == "IDENTIFIER") {
          head->setName(tok.value);
        } else {
          return NULL; // SYNTAX ERROR
        }
        tok = scanner.nextToken();
        if (tok.label != "LPAREN") {
          return NULL; // SYNTAX ERROR
        }
        while (tok.label != "RPAREN") {
          tok = scanner.nextToken();
          if (tok.label != "IDENTIFIER") {
            return NULL; // SYNTAX ERROR
          }
          tok = scanner.nextToken();
          if (tok.label == "RPAREN") {
            break;
          } else if (tok.label != "COMMA") {
            return NULL; // SYNTAX ERROR
          }
        }
        if (tok.label == "SEMICOLON") {
            head->adopt(parseCompoundStatement());
            tok = scanner.nextToken();
            if (tok.label == "DOT") {
                return head;
            }
        }
    }

    return NULL; // SYNTAX ERROR SOMEWHERE
}

parseTree *Parser::parseCompoundStatement() {
    parseTree *head = new parseTree(NodeType::COMPOUND);
    Token tok = scanner.nextToken();
    if (tok.label == "BEGIN") {
        head->adopt(parseStatement());
        tok = scanner.nextToken();
        while (tok.label == "SEMICOLON") {
            head->adopt(parseStatement());
            tok = scanner.nextToken();
        }
        if (tok.label == "END") {
            return head;
        }
    }
    return NULL; // SYNTAX ERROR SOMEWHERE
}

// parseTree *parseTree::parseStatement(std::string exp) {
//     std::vector<char*> list;
//     for(int i = 0; exp.length(); i++) {
//         list.push_back(&exp[i]);
//     }
//     std::stack<parseTree*> stack;
//     parseTree *head = new parseTree("");
//     std::vector<std::string> vect{"+", "-", "*", "/"};
//     std::vector<std::string> vect1{"+", "-", "*", "/", ")"};

//     stack.push(head);
//     parseTree *curr = head;
    
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
//             parseTree *root = stack.top();
//             stack.pop();
//             curr = root;
//         }
//     }
//     return head;
// }