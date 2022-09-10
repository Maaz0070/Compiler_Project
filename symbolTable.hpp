#include <iostream>

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
};

class symbolTable {
    public:
    symbolTable(){}
    int hashFunction(std::string token);
    std::string look_up(std::string token);
    bool insert(std::string token,
                std::string scope, 
                std::string type,
                int line);

    private:
    const int maxSize = 100;
    
};