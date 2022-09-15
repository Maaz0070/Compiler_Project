#include <iostream>

class parseTree {
    public:
    parseTree(std::string id);
    parseTree *parseStatement(std::string exp);
    void insertLeft(std::string newId);
    void insertRight(std::string newId);
    parseTree *getLeftChild();
    parseTree *getRightChild();
    void setId(std::string id);
    std::string getId();

    private:
    std::string id;
    parseTree *leftChild;
    parseTree *rightChild;
};