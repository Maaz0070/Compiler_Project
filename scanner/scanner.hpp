#ifndef SCANNER_H
#define SCANNER_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <stack>

enum tokenTypes {
    WORD,
    INTEGERS,
    DECIMAL,
    SPECIAL1,
    SPECIAL2,
    INVALID,
    QUOTES
};

struct Token {
    std::string value;
    std::string label;
    tokenTypes type;
    bool isKeyword;
    int line;
};

class Scanner {
    private:
        std::string fileName;
        std::ifstream file;
        int line;
        char currentChar;
        char nextChar;
        bool consumingString;
        bool foundOp;
        std::vector< std::vector<int> > transitionTable;
        std::set<char> special1char;
        std::set<char> special2char;
        std::set<char> invalidchar;
        std::set<std::string> special3char;
        std::unordered_map<std::string, std::string> lookupKeywords;
        std::unordered_map<std::string, std::string> lookupOperators;
        std::stack<char> opStack;
        std::string errString;
        Token curTok;

        
    
    public:
        Scanner();
        Scanner(std::string fileName);
        void look_up(Token& res);
        void getTokenType(Token& res, int state);
        bool isEOF;
        Token nextToken();
        Token getCurTok();
        void putBackToken();
        int getTransition(char input);
        int nextState(int curState, char input);
};

#endif