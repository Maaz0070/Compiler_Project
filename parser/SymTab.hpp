#include <unordered_map>
#include <string>

class SymTabNode {
    public:
        SymTabNode(std::string id, std::string scope, std::string type, int line) {
            this->id = id;
            this->scope = scope;
            this->type = type;
            this->line = line;
        }
    private:
      std::string id;
      std::string type;
      std::string scope;
      int line;
};

class SymTab {
public:
    SymTab();
    ~SymTab();
    void insert(std::string name, int value);
    int lookup(std::string name);
    void print();
private:
    std::unordered_map<std::string, SymTabNode> table;
};
};