#include "SymTab.hpp"
#include <iostream>


SymTabNode::SymTabNode(std::string id, std::string scope, std::string type, int line) {
    this->id = "";
    this->scope = "";
    this->type = "";
    this->line = 0;
} 

SymTab::SymTab() {
    table = std::unordered_map<std::string, SymTabNode>();
}

SymTab::~SymTab() {
    table.clear();
}

void SymTabNode::setId(int id) {
    this->id = id;
}

void SymTabNode::setScope(std::string scope) {
    this->scope = scope;
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

std::string SymTabNode::getScope() {
    return this->scope;
}

std::string SymTabNode::getType() {
    return this->type;
}

int SymTabNode::getLine() {
    return this->line;
}

void SymTab::insert(std::string name, int value) {
    table.insert(std::pair<std::string, SymTabNode>(name, SymTabNode(name, "", "", value)));
}

int SymTab::lookup(std::string name) {
    if (table.find(name) != table.end()) {
        return table[name].getLine();
    }
    return -1;
}

void SymTab::print() {
    for (auto it = table.begin(); it != table.end(); it++) {
        std::cout << it->first << " " << it->second.getLine() << std::endl;
    }
}