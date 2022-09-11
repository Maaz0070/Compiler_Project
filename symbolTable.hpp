#include <iostream>
const int max = 100;

class Node {
    std::string token;
    std::string type;
    std::string scope;
    int line;
    //name, type, size, dimension, line of Decleration, line of usage, address
    Node *next;

    public:
    Node() {
        next = NULL;
    }
    Node(std::string token, std::string scope, std::string type, int line) {
        token = token;
        scope = scope;
        type = type;
        line = line;
    }

    friend class symbolTable;
};

class symbolTable {
    public:
    symbolTable(){}
    int hashFunction(std::string token);
    Node* look_up(std::string token);
    bool insert(std::string token,
                std::string scope, 
                std::string type,
                int line);

    private:
    int maxSize = max;
    Node* head[max];
    
};