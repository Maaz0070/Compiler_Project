#include "scanner.hpp"
#include <fstream>


Scanner::Scanner(std::string fileName) {
    file.open(fileName);
    if(!file){
        std::cerr <<"Error: file not found.";
        exit(1);
    } 

    // used for state transitions to get next state val
    // rows: state
    // columns: transition (current character)
    // column lables: [ [A-Z, a-z, _], [0-9], [speicalChars], [specialSuffixes] ]
    transitionTable = {
        {1, 2, 3, 3},         // state 0
        {1, 1, -1, -1},       // state 1
        {-1, 2, -1, -1,},     // state 2
        {-1, -1, -1, 4,},     // state 3
        {-1, -1, -1, -1},     // state 4
    };
    specialChars = {'+', '-', '*', '/', ';', ':', '>', '<', '(', ')', '[', ']', ',', ';', '"'};
    specialSuffixes = {'=', '.', '&', '|'};
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
        res.type = NUMBER;
        break;
      case 3:
        res.type = SPECIAL;
        break;
      case 4:
        res.type = SPECIAL;
        break;
      case 5:
        res.type = STRLITERAL;
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
    } else if (res.type==SPECIAL){
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
  return cur == ' ' || cur == '\t' || cur == '\n' || cur == '\r';
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

      if (cur == '\'') {
        consumingString = !consumingString;
        flag = true;
        //return res;
      }
      
      if (consumingString){
        if (flag) {
          flag = false;
          look_up(res);
          return res;
        }
        tmpString += cur;
        cur = file.get();
        while (cur != '\'') {
          tmpString += cur;
          cur = file.get();
        }
        res.type = STRLITERAL;

        if (tmpString.length() > 1) {
          res.value = "\'" + tmpString + '\'';
          consumingString = !consumingString;
          look_up(res);
          return res;
        } else {
          res.value += " ";
          look_up(res);
          return res;
        }
        
      }
      
      if ((cur == ' ' || cur == '\t' || cur == '\n' || cur == '\r')){
        if (cur == '\n') {
          line++;
        }
        if (res.value != "") {
          look_up(res);
          return res;
        }
        continue;
      }
      // do not read comments
      if (cur == '{') {
        while (cur != '}') {
          cur = file.get();
        }
        file.get();
        continue;
      }
      if (cur == '/') {
        if (file.get()=='/') {
          while (cur != '\n') {
            cur = file.get();
          }
          continue;
        } else {
          file.putback(cur);
        }
        file.get();
        continue;
      }

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
      
      if (isalpha(cur) || cur == '_') {
        state = transitionTable[state][0];
      } else if (isdigit(cur)) {
        state = transitionTable[state][1];
      } else if (specialChars.find(cur) != specialChars.end()) {
        state = transitionTable[state][2];
      } else if (specialSuffixes.find(cur) != specialSuffixes.end()) { // this is for special chars that have 2 chars (<=, &&, ..)
        state = transitionTable[state][3];
      } else {
        state = -1;
      } 
      if (state!=-1) res.value += cur;
      else file.putback(cur);
    }
    
    look_up(res);
    return res; 
}