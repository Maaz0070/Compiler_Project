#include "symbolTable.hpp"

symbolTable::symbolTable(){
    for(int i = 0; i < max; i++) {
        head[i] = NULL;
    }
}

int symbolTable::hashFunction(std::string id) {
    int asc = 0;

    for(int i = 0; i < id.length(); i++) {
        asc = asc + id[i];
    }

    return asc % max;
}

Node* symbolTable::look_up(std::string id) {
    int hash = hashFunction(id);
    Node *ptr = head[hash];

    while(ptr != NULL) {
        //looptr through nodes
        if(ptr->id == id) {
            return ptr;
        }

        ptr = ptr->next;
    }
    return &Node();
}

void symbolTable::insert(std::string id, std::string scope, std::string type, int line) {
    int hash = hashFunction(id);
    Node *n = new Node(id, scope, type, line);

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

void symbolTable::deleteNode(std::string id) {
    int hash = hashFunction(id);
    Node *ptr = head[hash];
    Node *tmp = head[hash];

    if(ptr == NULL) {
        std::cout << "id doesn't exist";
    }

    if(ptr->id == id && ptr->next == NULL) {
        ptr->next = NULL;
        delete ptr;
    }

    while(ptr->id != id && ptr->next != NULL) {
        tmp = ptr;
        ptr = tmp->next;
    }

    if(ptr->id == id && ptr->next != NULL) {
        tmp->next = ptr->next;
        ptr->next = NULL;
        delete ptr;
    }
    else {
        tmp->next = NULL;
        ptr->next = NULL;
        delete ptr;
    }
    std::cout << "id doesn't exist";

}

