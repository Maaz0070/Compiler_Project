#include "parseTree.hpp"
#include <string>
#include <vector>
#include <stack>

parseTree::parseTree(NodeType type) {
    this->type = type;
    this->name = "";
    this->value = 0;
    this->parent = NULL;
    this->children = {};
}

void parseTree::setName(std::string name) {
    this->name = name;
}
std::string parseTree::getName() {
    return this->name;
}
void parseTree::setType(NodeType type) {
    this->type = type;
}
NodeType parseTree::getType() {
    return this->type;
}
void parseTree::setValue(int val) {
    this->value = val;
}
int parseTree::getValue() {
    return this->value;
}
void parseTree::setParent(parseTree *parent) {
    this->parent = parent;
}
parseTree *parseTree::getParent() {
    return this->parent;
}
void parseTree::adopt(parseTree *child) {
    this->children.push_back(child);
    child->setParent(this);
}
std::vector<parseTree *> parseTree::getChildren() {
    return this->children;
}

// parseTree *parseTree::parseStatement(std::string exp) {
//     std::vector<char*> list;
//     for(int i = 0; exp.length(); i++) {
//         list.push_back(&exp[i]);
//     }
//     std::stack<parseTree*> stack;
//     parseTree *head = new parseTree("");
//     std::vector<std::string> vect{"+", "-", "*", "/"};
//     std::vector<std::string> vect1{"+", "-", "*", "/", ")"};

//     stack.push(head);
//     parseTree *curr = head;
    
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
//             parseTree *root = stack.top();
//             stack.pop();
//             curr = root;
//         }
//     }
//     return head;
// }

// void parseTree::insertLeft(std::string newId) {
//     if(this->leftChild == NULL) {
//         this->leftChild = new parseTree(newId);
//     }
//     else {
//         parseTree *n = new parseTree(newId);
//         n->leftChild = this->leftChild;
//         this->leftChild = n;
//     }
// }

// void parseTree::insertRight(std::string newId) {
//     if(this->rightChild == NULL) {
//         this->rightChild = new parseTree(newId);
//     }
//     else {
//         parseTree *n = new parseTree(newId);
//         n->rightChild = this->rightChild;
//         this->rightChild = n;
//     }
// }

// parseTree *parseTree::getRightChild() {
//     return this->rightChild;
// }

// parseTree *parseTree::getLeftChild() {
//     return this->leftChild;
// }

// void parseTree::setId(std::string id) {
//     this->id = id;
// }

// std::string parseTree::getId() {
//     return this->id;
// }