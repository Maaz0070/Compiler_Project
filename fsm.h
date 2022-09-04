#include <vector>

enum reservedWords {
    PROGRAM, BEGIN, END, VAR, INTEGER, REAL, BOOLEAN, PROCEDURE, FUNCTION, IF, THEN, ELSE, WHILE, DO, NOT, AND, OR, TRUE, FALSE
};

enum operators {
    PLUS = '+', MINUS = '-', MULT = '*', DIV = "div", EQUAL = '=', NOTEQUAL = "not", LESSTHAN = '<', LESSTHANEQUAL = "<=", GREATERTHAN = '>', GREATERTHANEQUAL = ">=", ASSIGN = ":="
};

enum class PascalTokens {
  // Reserved words
  PROGRAM,
  BEGIN,
  END,
  VAR,
  INTEGER,
  REAL,
  PROCEDURE,
  FUNCTION,
  IF,
  THEN,
  ELSE,
  WHILE,
  DO,
  REPEAT,
  UNTIL,
  FOR,
  TO,
  DOWNTO,
  CASE,
  OF,
  GOTO,
  // Operators
  PLUS,
  MINUS,
  STAR,
  SLASH,
  ASSIGN,
  EQUAL,
  NOT_EQUAL,
  LESS,
  LESS_EQUAL,
  GREATER,
  GREATER_EQUAL,
  LPAREN,
  RPAREN,
  LBRACK,
  RBRACK,
  COMMA,
  COLON,
  SEMICOLON,
  PERIOD,
  DOTDOT,
  // Identifiers
  IDENT,
  // Constants
  INTEGER_CONST,
  REAL_CONST,
  // Special tokens
  END_OF_FILE,
  ERROR
};



class Fsm {
  private:
    int state;
    int nextState;
    int input;
    int output;
    int finalState;
    int initialState;
    int errorState;
    static const std::vector<std::vector<int>> transitionTable;
 


  public:
    static int nextState(int state, char input);
    static bool isFinal(int state);
    static bool isError(int state);
    static bool isValid(int state);
    static PascalTokens getToken(int state);


}

