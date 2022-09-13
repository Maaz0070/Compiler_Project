#include "parseTree.hpp"
#include <string>
#include <vector>
#include <stack>

parseTree::parseTree(std::string token) {
    this->token = token;
    this->leftChild = NULL;
    this->rightChild = NULL;
}

parseTree *parseTree::parseProgram(std::string exp) {
    std::vector<char*> list;
    for(int i = 0; exp.length(); i++) {
        list.push_back(&exp[i]);
    }
    std::stack<parseTree*> stack;
    parseTree *head = new parseTree("");
    std::vector<std::string> vect{"+", "-", "*", "/"};
    std::vector<std::string> vect1{"+", "-", "*", "/", ")"};

    stack.push(head);
    parseTree *curr = head;
    
    for(int i = 0; i < list.size(); i++) {
        if(list[i] == "(") {
            curr->insertLeft("");
            stack.push(curr);
            curr = curr->getLeftChild();
        }
        else if(find(vect.begin(), vect.end(), list[i]) != vect.end()) {
            curr->setToken(list[i]);
            curr->insertRight("");
            stack.push(curr);
            curr = curr->getRightChild();
        }
        else if(list[i] == ")") {
            curr = stack.top();
            stack.pop();
        }
        else if(find(vect1.begin(), vect1.end(), list[i]) == vect1.end()) {
            curr->setToken(list[i]);
            parseTree *root = stack.top();
            stack.pop();
            curr = root;
        }
    }
    return head;
}

void parseTree::insertLeft(std::string newToken) {
    if(this->leftChild == NULL) {
        this->leftChild = new parseTree(newToken);
    }
    else {
        parseTree *n = new parseTree(newToken);
        n->leftChild = this->leftChild;
        this->leftChild = n;
    }
}

void parseTree::insertRight(std::string newToken) {
    if(this->rightChild == NULL) {
        this->rightChild = new parseTree(newToken);
    }
    else {
        parseTree *n = new parseTree(newToken);
        n->rightChild = this->rightChild;
        this->rightChild = n;
    }
}

parseTree *parseTree::getRightChild() {
    return this->rightChild;
}

parseTree *parseTree::getLeftChild() {
    return this->leftChild;
}

void parseTree::setToken(std::string token) {
    this->token = token;
}

std::string parseTree::getToken() {
    return this->token;
}