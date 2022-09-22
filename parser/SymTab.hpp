#include <unordered_map>
#include <string>
#include <iostream>
#include "SymTabNode.hpp"

class SymTab {
public:
    SymTab();
    ~SymTab();
    void insert(std::string name);
    int lookup(std::string name);
    void output(std::ostream& os=std::cout);
private:
    std::unordered_map<std::string, SymTabNode> table;
};