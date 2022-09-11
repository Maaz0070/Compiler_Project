#include "scanner.hpp"
#include <fstream>


#define ALPHA 0
#define INTEGER 1
#define DEC 2
#define SPEC1 3
#define SPEC2 4 
#define QUOTE 5
#define SPACE 6
#define INVC 7


Scanner::Scanner(std::string fileName) {
/*
    input: takes in filename as a string which uses to open a file stream.
    output: a stream of tokens.
    Functionality: To read and check if the file can be opned, if not the code
                   exits with an error message.
*/
    file.open(fileName);
    if(!file){
        std::cerr <<"Error: file not found.";
        exit(1);
    } 

    // sets used for state transitions
    special1char = {'+', '-', '*', '/', ';', '<', '>','(', ')', '[', ']', ',', ';', '"', '{', '}', '^', ':'}; // first
    special2char = {'=', '>'}; // second
    special3char = {">=", "<=", "<>", ".." , ":="}; //   
    invalidchar = {'?', '!'};

    // 
    lookupKeywords = {
      {"and","AND"},
      {"array","ARRAY"},
      {"asm","ASM"},
      {"begin","BEGIN"},
      {"break","BREAK"},
      {"case","CASE"},
      {"const","CONST"},
      {"constructor","CONSTRUCTOR"},
      {"continue","CONTINUE"},
      {"destructor","DESTRUCTOR"},
      {"div","DIV"},
      {"do","DO"},
      {"downto","DOWNTO"},
      {"else","ELSE"},
      {"end","END"},
      {"FALSE","FALSE"},
      {"file","FILE"},
      {"for","FOR"},
      {"function","FUNCTION"},
      {"goto","GOTO"},
      {"if","IF"},
      {"implementation","IMPLEMENTATION"},
      {"in","IN"},
      {"inline","INLINE"},
      {"interface","INTERFACE"},
      {"label","LABEL"},
      {"mod","MOD"},
      {"nil","NIL"},
      {"not","NOT"},
      {"object","OBJECT"},
      {"of","OF"},
      {"on","ON"},
      {"operator","OPERATOR"},
      {"or","OR"},
      {"packed","PACKED"},
      {"procedure","PROCEDURE"},
      {"program","PROGRAM"},
      {"record","RECORD"},
      {"repeat","REPEAT"},
      {"set","SET"},
      {"shl","SHL"},
      {"shr","SHR"},
      {"string","STRING"},
      {"then","THEN"},
      {"to","TO"},
      {"TRUE","TRUE"},
      {"type","TYPE"},
      {"unit","UNIT"},
      {"until","UNTIL"},
      {"uses","USES"},
      {"var","VAR"},
      {"while","WHILE"},
      {"with","WITH"},
      {"xor","XOR"},
      {"(integer)","INTEGER"},
      {"(real number)","REAL"},
      {"(identifier)","INDENTIFIER"},
    };
    lookupOperators = {
      {"+","PLUSOP"},
      {"-","MINUSOP"},
      {"*","MULTOP"},
      {":", "COLON"},
      {"/","DIVOP"},
      {":=","ASSIGN"},
      {"=","EQUAL"},
      {"<>","NE"},
      {"<=","LTEQ"},
      {">=","GTEQ"},
      {"<","LT"},
      {">","GT"},
      {"..","DOTDOT"},
      {"+='","PLUSEQUAL"},
      {"-=","MINUSEQUAL"},
      {"*=","MULTEQUAL"},
      {"/=","DIVEQUAL"},
      {"^","CARAT"},
      {";","SEMICOLOR"},
      {".", "PERIOD"},
      {",","COMMA"},
      {"(","LPAREN"},
      {")","RPAREN"},
      {"[","LBRACKET"},
      {"]","RBRACKET"},
      {"{","LBRACE"},
      {"}","RBRACE"},
      {"(*","LCOMMENT"},
      {"*)","RCOMMENT"},
    };

    line = 1;
    consumingString = false;
    isEOF = false;
    foundOp = false;
}

// assigns a type a token depending on curState
void Scanner::getTokenType(Token& res, int state) {
  switch (state) {
      case 0:
        res.type = INVALID;
        break;
      case 1:
        res.type = WORD;
        break;
      case 2:
        res.type = INTEGERS;
        break;
      case 3:
        res.type = DECIMAL;
        break;
      case 4:
        res.type = SPECIAL1;
        break;
      case 5:
        res.type = SPECIAL2;
        break;
      case 6:
        res.type = QUOTES;
        break;
      default:
        res.type = INVALID;
        break;
    }
  // check if the token is a keyword
}

// converts a string to lowercase
std::string toLower(std::string str) {
    std::string res = "";
    for (int i = 0; i < str.length(); i++) {
        res += tolower(str[i]);
    }
    return res;
}

// checks if token label is part of keyword set, creates labels
void Scanner::look_up(Token& res) {
    res.isKeyword = false;
    if (res.type == WORD) {
      if (lookupKeywords.find(toLower(res.value)) != lookupKeywords.end()) {
        res.label = lookupKeywords[toLower(res.value)];
        res.isKeyword = true;
      } else {
        res.label = "IDENTIFIER";
      }
    } 
    else if (res.type == SPECIAL1 || res.type == SPECIAL2) {
      if (lookupOperators.find(res.value) != lookupOperators.end()) {
        res.label = lookupOperators[res.value];
      }
    } else if (res.type == INTEGERS) {
      res.label = "INTEGER";
    } else if (res.type == DECIMAL) {
      res.label = "REAL";
    } else if (res.type == QUOTES) {
      res.label = "STRING";
    } 
    else if (res.type == INVALID) {
      res.label = "INVALID";
    } 
    return;
}

bool isWhitespace(char cur) {
  return cur == ' ' || cur == '\t' || cur == '\n' || cur == '\r' || cur == '\0';
}

// scans source file for next token and returns it
Token Scanner::nextToken() {
    char cur = '1';
    int state = 0;
    std::string tmpString = "";
    Token res;
    res.value = "";
    bool flag = false;
    bool qflag = false;
    bool dflag = false;

    // loop until end of file or null character
    while (!file.eof() && cur != '\0') {
      cur = file.get();
      if (cur == '\n') line++;
      if (cur == EOF) {
        state = 8; // END STATE
        isEOF = true;
        getTokenType(res, state);
        look_up(res);
        if (res.value.length() == 0) {
          res.value = "EOF";
          res.label = "INVALID";
        }
        return res;
      }
      getTokenType(res, state);
      res.line = line;

      if (state==0 && isWhitespace(cur)) {
        continue;
      }

      // handles brackets and parenthesis and checks if they are valid
      if (cur == '(' || cur == '[' || cur == '{') {
        if (res.value.length()>0) {
          file.unget();
          getTokenType(res, state);
          look_up(res);
          return res;
        }
        opStack.push(cur);
        res.type = SPECIAL1;
        res.value = cur;
        look_up(res);
        return res;
      }
      if (cur == ')' || cur == ']' || cur == '}') {
        if (res.value.length()>0) {
          file.unget();
          getTokenType(res, state);
          look_up(res);
          return res;
        }
        if (opStack.empty()) {
          res.type = INVALID;
          res.value = cur;
          look_up(res);
          return res;
        }
        char top = opStack.top();
        if ((top == '(' && cur == ')') || (top == '[' && cur == ']') || (top == '{' && cur == '}')) {
          opStack.pop();
          res.type = SPECIAL1;
          res.value = cur;
          look_up(res);
          return res;
        } else {
          res.type = INVALID;
          res.value = cur;
          look_up(res);
          return res;
        }
      }

      if (cur == '\''){
        qflag = !qflag;
        if (!qflag) {
          res.value += '\'';
          getTokenType(res, state);
          look_up(res);
          return res;
        }
      }
      
      // handle string literals
      if (special1char.find(cur) != special1char.end() && !qflag) {
        if (res.value.length() > 0) {
          file.putback(cur);
          getTokenType(res, state);
          look_up(res);
          return res;
        }

        if (cur=='.') {
          foundOp = !foundOp;
        }
        if (foundOp) {
          state = 0;
          if (res.value != "") {
            getTokenType(res, state);
            look_up(res);
            return res;
          }
          continue;
        }
        

        char tmp = cur;
        std::string tmpString = "";
        cur = file.get();
        if (special1char.find(cur) != special1char.end() || special2char.find(cur) != special2char.end()) {
          tmpString.push_back(tmp);
          tmpString.push_back(cur);
          if (special3char.find(tmpString) != special3char.end()) {
            res.value = tmpString;
            getTokenType(res, 5);
            look_up(res);
            return res;
          } 
          
        } else {

        }
        file.putback(cur);
        cur = tmp;
        res.value = cur;
        getTokenType(res, 4);
        look_up(res);
        return res;
      }
      

      state = nextState(state, cur);
      if (state == 3 && cur == '.') {
        dflag = true;
        res.value += cur;
      }
      else if (state < 0 && dflag) {
        res.value += cur;
        errString = res.value;
      } 
      else if (state == 0) {
        if (errString.length() > 0) {
          errString = "";
          dflag = !dflag;
        }
        if (!isWhitespace(cur) && !(invalidchar.find(cur) != invalidchar.end())) res.value += cur;
        if (invalidchar.find(cur) != invalidchar.end())
          file.putback(cur);
        look_up(res);
        return res; 
      }
      else 
        if (qflag || !isWhitespace(cur))
          res.value += cur;
    }
    return res;
}

// returns encoded FSM transition depending on current character
int Scanner::getTransition(char input) {
  if (isalpha(input) || input == '_' ) {
    return 0;
  } else if (isdigit(input)) {
    return 1;
  } else if (input == '.') {
    return 2;
  }
  else if (special1char.find(input) != special1char.end()) {
    return 3;
  } 
  else if (special2char.find(input) != special2char.end()) {
    return 4;
  }
  else if (input == '\'') {
    return 5;
  } 
  else if (isWhitespace(input)) {
    return 6;
  } 
  else if (invalidchar.find(input) != invalidchar.end()) {
    return 7;
  }
  else {
    return -1;
  }
}

// generates next state for FSM
int Scanner::nextState(int curState, char input) {
  int transition = getTransition(input);

  switch(curState) {
    // 
    case 0:
    // START
      if (transition == ALPHA) return 1;
      else if (transition == INTEGER) return 2;
      else if (transition == DEC) return 4;
      else if (transition == SPEC1) return 4;
      else if (transition == SPEC2) return 4;
      else if (transition == QUOTE) return 6;
      else if (transition == SPACE) return 0;
      else if (transition == INVC) return 7;
      else return -1;
      break;
    
    case 1:
      // WORD
      if (transition == ALPHA) return 1;
      else if (transition == INTEGER) return 1;
      else if (transition == DEC) return 0;
      else if (transition == SPEC1) return 0;
      else if (transition == SPEC2) return 0;
      else if (transition == QUOTE) return -1;
      else if (transition == SPACE) return 0;
      else if (transition == INVC) return 0;
      else return -1;
      break;
    case 2:
      // INTEGER
      if (transition == ALPHA) return -1;
      else if (transition == INTEGER) return 2;
      else if (transition == DEC) return 3;
      else if (transition == SPEC1) return 0;
      else if (transition == SPEC2) return 0;
      else if (transition == QUOTE) return -1;
      else if (transition == SPACE) return 0;
      else if (transition == INVC) return 0;
      else return -1;
      break;
    case 3:
      // DECIMAL
      if (transition == ALPHA) return -1;
      else if (transition == INTEGER) return 3;
      else if (transition == DEC) return -1;
      else if (transition == SPEC1) return 0;
      else if (transition == SPEC2) return 0;
      else if (transition == QUOTE) return -1;
      else if (transition == SPACE) return 0;
      else if (transition == INVC) return 0;
      else return -1;
      break;
    case 4:
      // SPECIAL1
      if (transition == ALPHA) return 0;
      else if (transition == INTEGER) return 0;
      else if (transition == DEC) return 0;
      else if (transition == SPEC1) return 0;
      else if (transition == SPEC2) return 5;
      else if (transition == QUOTE) return 0;
      else if (transition == SPACE) return 0;
      else if (transition == INVC) return 0;
      else return -1;
      break;
    case 5:
      // SPECIAL2
      if (transition == ALPHA) return 0;
      else if (transition == INTEGER) return 0;
      else if (transition == DEC) return 0;
      else if (transition == SPEC1) return 0;
      else if (transition == SPEC2) return 0;
      else if (transition == QUOTE) return 0;
      else if (transition == SPACE) return 0;
      else if (transition == INVC) return 0;
      else return -1;
      break;
    case 6:
      // QUOTE
      if (transition == ALPHA) return 6;
      else if (transition == INTEGER) return 6;
      else if (transition == DEC) return 6;
      else if (transition == SPEC1) return 6;
      else if (transition == SPEC2) return 6;
      else if (transition == QUOTE) return 0;
      else if (transition == SPACE) return 6;
      else if (transition == INVC) return 0;
      else return -1;
      break;
    // ERROR
    case 7:
      // INVALID
      if (transition == ALPHA) return 0;
      else if (transition == INTEGER) return 0;
      else if (transition == DEC) return 0;
      else if (transition == SPEC1) return 0;
      else if (transition == SPEC2) return 0;
      else if (transition == QUOTE) return 0;
      else if (transition == SPACE) return 0;
      else if (transition == INVC) return 0;
      else return -1;
      break;
    case 8:
      // END STATE
      if (transition == ALPHA) return 0;
      else if (transition == INTEGER) return 0;
      else if (transition == DEC) return 0;
      else if (transition == SPEC1) return 0;
      else if (transition == SPEC2) return 0;
      else if (transition == QUOTE) return 0;
      else if (transition == SPACE) return 0;
      else if (transition == INVC) return 0;
      else return -1;
      break;
    // ERROR State
    case -1:
      if (transition == ALPHA) return -1;
      else if (transition == INTEGER) return -1;
      else if (transition == DEC) return -1;
      else if (transition == SPEC1) return -1;
      else if (transition == SPEC2) return -1;
      else if (transition == QUOTE) return -1;
      else if (transition == SPACE) return 0;
      else if (transition == INVC) return -1;
      else return -1;
      break;

    default:
      return -1;
      break;
  }
}