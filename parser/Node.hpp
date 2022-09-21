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
    PROGRAM, COMPOUND, ASSIGN, LOOP, TEST, WRITE, WRITELN, LIST,
    ADD, SUBTRACT, OR, MULTIPLY, DIVIDE, IN, EQ, LT, GT, NE, LTEQ, GTEQ,NEGATE, POS, NOT, DOTDOT,
    VARIABLE, INTEGER_CONSTANT, REAL_CONSTANT, STRING_CONSTANT, GOTO, EMPTY, IF, CASE, COND, THEN, ELSE, CASEELEM,
    REPEAT, UNTIL
};

class Node {
    public:
        Node(NodeType type);
        void setName(std::string name);
        std::string getName();
        void setType(NodeType type);
        NodeType getType();
        std::string getTypeString();
        void setValue(double val);
        double getValue();
        void setLine(int l);
        int getLine();
        void setParent(Node *parent);
        Node *getParent();
        void adopt(Node *child);
        std::vector<Node *> getChildren();

    private:
        NodeType type;
        std::string name;
        double value;
        Node *parent;
        std::vector<Node*> children;
        int line;
};