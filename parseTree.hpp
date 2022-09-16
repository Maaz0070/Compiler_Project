#include <iostream>
#include <vector>

// class parseTree {
//     public:
//     parseTree(std::string id);
//     parseTree *parseStatement(std::string exp);
//     void insertLeft(std::string newId);
//     void insertRight(std::string newId);
//     parseTree *getLeftChild();
//     parseTree *getRightChild();
//     void setId(std::string id);
//     std::string getId();

//     private:
//     std::string id;
//     parseTree *leftChild;
//     parseTree *rightChild;
// };

enum class NodeType {
    PROGRAM, COMPOUND, ASSIGN, LOOP, TEST, WRITE, WRITELN,
    ADD, SUBTRACT, MULTIPLY, DIVIDE, EQ, LT,
    VARIABLE, INTEGER_CONSTANT, REAL_CONSTANT, STRING_CONSTANT
};

class parseTree {
    public:
    parseTree(NodeType type);
    void setName(std::string name);
    std::string getName();
    void setType(NodeType type);
    NodeType getType();
    void setValue(int val);
    int getValue();
    void setParent(parseTree *parent);
    parseTree *getParent();
    void addChild(parseTree *child);
    parseTree *getChildren();

    private:
    NodeType type;
    std::string name;
    int value;
    parseTree *parent;
    std::vector<parseTree*> children;
};