#include <iostream>
const int max = 100;

class Node {
    //name, type, size, dimension, line of Decleration, line of usage, address
    std::string token;
    std::string type;
    std::string scope;
    int line;
    Node *next;

    public:
    Node() {
        next = NULL;
    }
    Node(std::string token, std::string scope, std::string type, int line) {
        this->token = token;
        this->scope = scope;
        this->type = type;
        this->line = line;
    }

    friend class symbolTable;
};

class symbolTable {
    public:
    symbolTable();
    int hashFunction(std::string token);
    Node* look_up(std::string token);
    void insert(std::string token,
                std::string scope, 
                std::string type,
                int line);
    void deleteNode(std::string token);

    private:
    int maxSize = max;
    Node* head[max];
    
};