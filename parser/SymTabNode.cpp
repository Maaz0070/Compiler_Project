#include "SymTabNode.hpp"

SymTabNode::SymTabNode(std::string name, std::string type) {
    this->id = name;
    this->type = type;
}

SymTabNode::~SymTabNode() {
}


void SymTabNode::setId(std::string id) {
    this->id = id;
}

void SymTabNode::setType(std::string type) {
    this->type = type;
}

void SymTabNode::setLine(int line) {
    this->line = line;
}

std::string SymTabNode::getId() {
    return this->id;
}

std::string SymTabNode::getType() {
    return this->type;
}

int SymTabNode::getLine() {
    return this->line;
}