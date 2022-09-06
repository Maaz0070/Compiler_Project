#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>

// enum keyword {
//     // Reserved words
//     PROGRAM,
//     BEGIN,
//     END,
//     VAR,
//     INTEGER,
//     REAL,
//     PROCEDURE,
//     FUNCTION,
//     IF,
//     THEN,
//     ELSE,
//     WHILE,
//     DO,
//     REPEAT,
//     UNTIL,
//     FOR,
//     TO,
//     DOWNTO,
//     CASE,
//     OF,
//     GOTO,
//     // Operators
//     PLUS,
//     MINUS,
//     STAR,
//     SLASH,
//     ASSIGN,
//     EQUAL,
//     NOT_EQUAL,
//     LESS,
//     LESS_EQUAL,
//     GREATER,
//     GREATER_EQUAL,
//     LPAREN,
//     RPAREN,
//     LBRACK,
//     RBRACK,
//     COMMA,
//     COLON,
//     SEMICOLON,
//     PERIOD,
//     DOTDOT,
//     // Identifiers
//     IDENT,
//     // Constants
//     INTEGER_CONST,
//     REAL_CONST,
//     // Special tokens
// };
enum tokenTypes {
    WORD,
    NUMBER,
    OPERATOR,
    SPECIAL,
    INVALID,
    STRLITERAL
};

struct Token {
    std::string value;
    tokenTypes type;
    std::string label;
    bool isKeyword;
};



class Scanner {
    private:
        std::string fileName;
        std::ifstream file;
        int line;
        char currentChar;
        char nextChar;
        bool consumingString;
        std::vector< std::vector<int> > transitionTable;
        std::set<char> specialChars;
        std::set<char> specialSuffixes;
        std::set<std::string> lookupKeywords;
        std::set<std::string> lookupOperators;
        
    
    public:
        Scanner(std::string fileName);
        void look_up(Token& res);
        bool isEOF;
        Token nextToken();
};