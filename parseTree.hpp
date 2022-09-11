#include <iostream>

class parseTree {
    public:
    parseTree(std::string token);
    parseTree *parseProgram(std::string exp);
    void insertLeft(std::string newToken);
    void insertRight(std::string newToken);
    parseTree *getLeftChild();
    parseTree *getRightChild();
    void setToken(std::string token);
    std::string getToken();

    private:
    std::string token;
    parseTree *leftChild;
    parseTree *rightChild;
};