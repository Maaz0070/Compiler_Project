#include "symbolTable.hpp"

symbolTable::symbolTable(){
    for(int i = 0; i < max; i++) {
        head[i] = NULL;
    }
}

int symbolTable::hashFunction(std::string token) {
    int asc = 0;

    for(int i = 0; i < token.length(); i++) {
        asc = asc + token[i];
    }

    return asc % max;
}

Node* symbolTable::look_up(std::string token) {
    int hash = hashFunction(token);
    Node *ptr = head[hash];

    while(ptr != NULL) {
        //looptr through nodes
        if(ptr->token == token) {
            return ptr;
        }

        ptr = ptr->next;
    }
    return &Node();
}

void symbolTable::insert(std::string token, std::string scope, std::string type, int line) {
    int hash = hashFunction(token);
    Node *n = new Node(token, scope, type, line);

    if(head[hash] == NULL) {
        head[hash] = n;
    }
    else {
        Node *ptr = head[hash];
        while(ptr->next != NULL) {
            ptr = ptr->next;
        }
        ptr->next = n;
    }
}

void symbolTable::deleteNode(std::string token) {
    int hash = hashFunction(token);
    Node *ptr = head[hash];
    Node *tmp = head[hash];

    if(ptr == NULL) {
        std::cout << "Token doesn't exist";
    }

    if(ptr->token == token && ptr->next == NULL) {
        ptr->next = NULL;
        delete ptr;
    }

    while(ptr->token != token && ptr->next != NULL) {
        tmp = ptr;
        ptr = tmp->next;
    }

    if(ptr->token == token && ptr->next != NULL) {
        tmp->next = ptr->next;
        ptr->next = NULL;
        delete ptr;
    }
    else {
        tmp->next = NULL;
        ptr->next = NULL;
        delete ptr;
    }
    std::cout << "Token doesn't exist";

}

