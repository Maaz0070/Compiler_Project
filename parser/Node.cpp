#include "Node.hpp"
#include <string>
#include <vector>
#include <stack>

Node::Node(NodeType ty) {
    type = ty;
    name = "";
    value = 0;
    parent = NULL;
    children = {};
}

void Node::setName(std::string newName) {
    name = newName;
}
std::string Node::getName() {
    return name;
}
void Node::setType(NodeType newType) {
    type = newType;
}
NodeType Node::getType() {
    return type;
}

std::string Node::getTypeString() {
    switch (type) {
        case NodeType::PROGRAM:
            return "PROGRAM";
            break;
        case NodeType::COMPOUND:
            return "COMPOUND";
            break;
        case NodeType::ASSIGN: 
            return "ASSIGN";
            break;
        case NodeType::LOOP:
            return "LOOP";
            break;
        case NodeType::VARIABLE:
            return "VARIABLE";
            break;
        case NodeType::INTEGER_CONSTANT:
            return "INTEGER_CONSTANT";
            break;
        default:
            return "UNKNOWN";
            break;
    }
}

void Node::setValue(int newVal) {
    value = newVal;
}
int Node::getValue() {
    return value;
}
void Node::setParent(Node *par) {
    parent = par;
}
Node *Node::getParent() {
    return parent;
}
void Node::adopt(Node *newChild) {
    children.push_back(newChild);
    newChild->setParent(this);
}
std::vector<Node *> Node::getChildren() {
    return children;
}

// Node *Node::parseStatement(std::string exp) {
//     std::vector<char*> list;
//     for(int i = 0; exp.length(); i++) {
//         list.push_back(&exp[i]);
//     }
//     std::stack<Node*> stack;
//     Node *head = new Node("");
//     std::vector<std::string> vect{"+", "-", "*", "/"};
//     std::vector<std::string> vect1{"+", "-", "*", "/", ")"};

//     stack.push(head);
//     Node *curr = head;
    
//     for(int i = 0; i < list.size(); i++) {
//         std::string currChar(list[i]);
//         if(list[i] == "(") {
//             curr->insertLeft("");
//             stack.push(curr);
//             curr = curr->getLeftChild();
//         }
//         else if(find(vect.begin(), vect.end(), currChar) != vect.end()) {
//             curr->setId(list[i]);
//             curr->insertRight("");
//             stack.push(curr);
//             curr = curr->getRightChild();
//         }
//         else if(list[i] == ")") {
//             curr = stack.top();
//             stack.pop();
//         }
//         else if(find(vect1.begin(), vect1.end(), list[i]) == vect1.end()) {
//             curr->setId(list[i]);
//             Node *root = stack.top();
//             stack.pop();
//             curr = root;
//         }
//     }
//     return head;
// }

// void Node::insertLeft(std::string newId) {
//     if(this->leftChild == NULL) {
//         this->leftChild = new Node(newId);
//     }
//     else {
//         Node *n = new Node(newId);
//         n->leftChild = this->leftChild;
//         this->leftChild = n;
//     }
// }

// void Node::insertRight(std::string newId) {
//     if(this->rightChild == NULL) {
//         this->rightChild = new Node(newId);
//     }
//     else {
//         Node *n = new Node(newId);
//         n->rightChild = this->rightChild;
//         this->rightChild = n;
//     }
// }

// Node *Node::getRightChild() {
//     return this->rightChild;
// }

// Node *Node::getLeftChild() {
//     return this->leftChild;
// }

// void Node::setId(std::string id) {
//     this->id = id;
// }

// std::string Node::getId() {
//     return this->id;
// }