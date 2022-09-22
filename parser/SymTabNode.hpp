#include <string>

class SymTabNode {
    public:
        SymTabNode(std::string name, std::string type);
        ~SymTabNode();
        void setId(std::string id);
        void setScope(std::string scope);
        void setType(std::string type);
        void setLine(int line);
        std::string getId();
        std::string getScope();
        std::string getType();
        int getLine();
    private:
      std::string id;
      std::string type;
      int line;
};