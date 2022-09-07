#include "scanner.hpp"
#include <fstream>


#define ALPHA 0
#define INTEGER 1
#define DEC 2
#define SPEC1 3
#define SPEC2 4 
#define QUOTE 5
#define SPACE 6
#define LPAREN 7
#define RPAREN 8
#define LBRACK 9
#define RBRACK 10
#define LCURL 11
#define RCURL 12

Scanner::Scanner(std::string fileName) {
    file.open(fileName);
    if(!file){
        std::cerr <<"Error: file not found.";
        exit(1);
    } 

    // used for state transitions to get next state val
    // rows: state
    // columns: transition (current character)
    // column lables: [ [A-Z, a-z, _], [0-9], [speicalChars], [special2char] ]
    // transitionTable = {
    //     {1, 2, 3, 3},         // state 0
    //     {1, 1, -1, -1},       // state 1
    //     {-1, 2, -1, -1, 3},
    //     {-1, 3, -1, -1, -1},     // state 2
    //     {-1, -1, -1, 4,},     // state 3
    //     {-1, -1, -1, -1},     // state 4
    // };
    special1char = {'+', '-', '*', '/', ';', '<', '>','(', ')', '[', ']', ',', ';', '"', '{', '}', '^', '.', ':'}; // first
    special2char = {'=', '>'}; // second
    special3char = {">=", "<=", "<>", ".." , ":="}; //   


    lookupKeywords = {"program", "begin", "end", "var", "integer", "real", "procedure", "function", "if", "then", "else", "while", "do", "repeat", "until", "for", "to", "downto", "case", "of", "goto"},
    lookupOperators = {"+", "-", "*", "/", ":=", "=", "<>", "<", "<=", ">", ">=", "(", ")", "[", "]", ",", ":", ";", ".", "..", };
    line = 0;
    consumingString = false;
    isEOF = false;
}

void getTokenType(Token& res, int state) {
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
}

std::string toLower(std::string str) {
    std::string res = "";
    for (int i = 0; i < str.length(); i++) {
        res += tolower(str[i]);
    }
    return res;
}

void Scanner::look_up(Token& res) {
    res.isKeyword = false;
    if (res.type == WORD) {
      for(auto keyword : lookupKeywords) {
        if(keyword == toLower(res.value)){
            res.label = keyword;
            res.isKeyword = true;
            return;
        }
      }
      res.label = "WORD";
    } else if (res.type==SPECIAL1){
      for(auto op : lookupOperators) {
        if(op == res.value){
            res.label = op;
            res.isKeyword = true;
            return;
        } 
      }
    } 
    res.label = "STRING";
    return;

}

bool isWhitespace(char cur) {
  return cur == ' ' || cur == '\t' || cur == '\n' || cur == '\r' || cur == '\0';
}

Token Scanner::nextToken() {
    char cur;
    int state = 0;
    std::string tmpString = "";
    Token res;
    res.value = "";
    bool flag = false;

    while (!file.eof() && state != -1) {
      cur = file.get();
      if (cur == EOF) {
        isEOF = true;
        getTokenType(res, state);
        look_up(res);
        return res;
      }
      getTokenType(res, state);

      if (state==0 && isWhitespace(cur)) {
        continue;
      }

      if (special1char.find(cur) != special1char.end()) {
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
          
        } 
        file.putback(cur);
        cur = tmp;
        res.value = cur;
        getTokenType(res, 4);
        return res;
      }

      if (cur == '(' || cur == '[' || cur == '{') {
        opStack.push(cur);
        res.type = SPECIAL1;
        res.value = cur;
        return res;
      }
      if (cur == ')' || cur == ']' || cur == '}') {
        if (opStack.empty()) {
          res.type = INVALID;
          res.value = cur;
          return res;
        }
        char top = opStack.top();
        if ((top == '(' && cur == ')') || (top == '[' && cur == ']') || (top == '{' && cur == '}')) {
          opStack.pop();
          res.type = SPECIAL1;
          res.value = cur;
          return res;
        } else {
          res.type = INVALID;
          res.value = cur;
          return res;
        }
      }

      // if (cur == '\'') {
      //   consumingString = !consumingString;
      //   flag = true;
      //   //return res;
      // }
      
      // if (consumingString){
      //   if (flag) {
      //     flag = false;
      //     look_up(res);
      //     return res;
      //   }
      //   tmpString += cur;
      //   cur = file.get();
      //   while (cur != '\'') {
      //     tmpString += cur;
      //     cur = file.get();
      //   }
      //   res.type = STRLITERAL;

      //   if (tmpString.length() > 1) {
      //     res.value = "\'" + tmpString + '\'';
      //     consumingString = !consumingString;
      //     look_up(res);
      //     return res;
      //   } else {
      //     res.value += " ";
      //     look_up(res);
      //     return res;
      //   }
        
      // }
      // if (cur == '\'') {
      //   consumingString = !consumingString;
      // }

      // if ((cur == ' ' || cur == '\t' || cur == '\n' || cur == '\r')){
      //   if (cur == '\n') {
      //     line++;
      //   }
      //   if (res.value != "") {
      //     look_up(res);
      //     return res;
      //   }
      //   continue;
      // }
      // do not read comments
      // if (cur == '{') {
      //   while (cur != '}') {
      //     cur = file.get();
      //   }
      //   file.get();
      //   continue;
      // }
      // if (cur == '/') {
      //   if (file.get()=='/') {
      //     while (cur != '\n') {
      //       cur = file.get();
      //     }
      //     continue;
      //   } else {
      //     file.putback(cur);
      //   }
      //   file.get();
      //   continue;
      // }

      // // handle string literals
      // if (cur == '\'') {
      //   while (cur != '\'') {
      //     res.value += cur;
      //     cur = file.get();
      //   }
      //   res.value += cur;
      //   res.type = STRLITERAL;
      //   return res;
      // }

      state = nextState(state, cur);
      if (state < 0) 
        std::cerr << "Error at line " << line << ": " << cur << " is not a valid character" << std::endl;
      else if (state == 0) {
        if (!isWhitespace(cur)) res.value += cur;
        look_up(res);
        return res; 
      }
      else 
        if (!isWhitespace(cur)) res.value += cur;
    //   if (isalpha(cur) || cur == '_') {
    //     state = transitionTable[state][0];
    //   } else if (isdigit(cur)) {
    //     state = transitionTable[state][1];
    //   } else if (special1char.find(cur) != special1char.end()) {
    //     state = transitionTable[state][2];
    //   } else if (special2char.find(cur) != special2char.end()) { // this is for special chars that have 2 chars (<=, &&, ..)
    //     state = transitionTable[state][3];
    //   } else {
    //     state = -1;
    //   } 
    //   if (state!=-1) res.value += cur;
    //   else file.putback(cur);
    // }
    }
}


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
  // else if (special2char.find(input) != special2char.end()) {
  //   return 4;
  // } 
  else if (input == '\'') {
    return 5;
  } else if (isWhitespace(input)) {
    return 6;
  }else {
    return -1;
  }
}

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
      else return -1;
      break;
    case 3:
      // DECIMAL
      if (transition == ALPHA) return -1;
      else if (transition == INTEGER) return 3;
      else if (transition == DEC) return 0;
      else if (transition == SPEC1) return 0;
      else if (transition == SPEC2) return 0;
      else if (transition == QUOTE) return -1;
      else if (transition == SPACE) return 0;
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
      else return -1;
      break;
    default:
      return -1;
      break;
  }
}