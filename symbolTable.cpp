#include "symbolTable.hpp"

int symbolTable::hashFunction(std::string token) {
    int asc = 0;

    for(int i = 0; i < token.length(); i++) {
        asc = asc + token[i];
    }

    return asc % symbolTable::maxSize;
}

Node* symbolTable::look_up(std::string token) {
    int hash = hashFunction(token);
    Node *n = head[hash];

    while(n != NULL) {
        //loop through nodes
        if(n->token == token) {
            return n;
        }
        else {
            return 0;
        }

    }
}

