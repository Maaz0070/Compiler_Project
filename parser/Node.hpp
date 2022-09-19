#include <iostream>
#include <vector>

// class Node {
//     public:
//     Node(std::string id);
//     Node *parseStatement(std::string exp);
//     void insertLeft(std::string newId);
//     void insertRight(std::string newId);
//     Node *getLeftChild();
//     Node *getRightChild();
//     void setId(std::string id);
//     std::string getId();

//     private:
//     std::string id;
//     Node *leftChild;
//     Node *rightChild;
// };

enum class NodeType {
    PROGRAM, COMPOUND, ASSIGN, LOOP, TEST, WRITE, WRITELN,
    ADD, SUBTRACT, MULTIPLY, DIVIDE, EQ, LT,
    VARIABLE, INTEGER_CONSTANT, REAL_CONSTANT, STRING_CONSTANT
};

class Node {
    public:
        Node(NodeType type);
        void setName(std::string name);
        std::string getName();
        void setType(NodeType type);
        NodeType getType();
        std::string getTypeString();
        void setValue(int val);
        int getValue();
        void setParent(Node *parent);
        Node *getParent();
        void adopt(Node *child);
        std::vector<Node *> getChildren();

    private:
        NodeType type;
        std::string name;
        int value;
        Node *parent;
        std::vector<Node*> children;
};