#include <iostream>
#include <vector>

enum class NodeType {
    PROGRAM, COMPOUND, ASSIGN, LOOP, TEST, WRITE, WRITELN, LIST,
    ADD, SUBTRACT, OR, MULTIPLY, DIVIDE, IN, EQ, LT, GT, NE, LTEQ, GTEQ,NEGATE, POS, NOT, DOTDOT,
    VARIABLE, INTEGER_CONSTANT, REAL_CONSTANT, STRING_CONSTANT, GOTO, EMPTY, IF, CASE, COND, THEN, ELSE, CASEELEM,
    REPEAT, UNTIL
};

class Node {
    public:
        Node(NodeType type, int newline);
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