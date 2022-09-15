#include <iostream>
const int max = 100;

class Node {
    //name, type, size, dimension, line of Decleration, line of usage, address
    std::string id;
    std::string type;
    std::string scope;
    int line;
    Node *next;

    public:
    Node() {
        next = NULL;
    }
    Node(std::string id, std::string scope, std::string type, int line) {
        this->id = id;
        this->scope = scope;
        this->type = type;
        this->line = line;
    }

    friend class symbolTable;
};

class symbolTable {
    public:
    symbolTable();
    int hashFunction(std::string id);
    Node* look_up(std::string id);
    void insert(std::string id,
                std::string scope, 
                std::string type,
                int line);
    void deleteNode(std::string id);

    private:
    int maxSize = max;
    Node* head[max];
    
};