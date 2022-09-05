#include "scanner.hpp"
#include <fstream>


Scanner::Scanner(std::string fileName) {
    file.open(fileName);
    if(!file){
        std::cerr <<"Error: file not found.";
        exit(1);
    } 

    // transition table (check discord for image)
    transitionTable = {
        {1, 2, 3, 3},
        {1, 1, -1, -1},
        {-1, 2, -1, -1,},
        {-1, -1, -1, 4,},
        {-1, -1, -1, -1},
    };
    specialChars = {'+', '-', '*', '/', ';', ':', '>', '<', '(', ')', '[', ']', ',', ';', '"'};
    specialSuffixes = {'=', '.', '&', '|'};
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
          return res;
        } else {
          res.value += " ";
          return res;
        }
        
      }
      
      if ((cur == ' ' || cur == '\t' || cur == '\n' || cur == '\r')){
        if (cur == '\n') {
          line++;
        }
        if (res.value != "") {
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

    

    return res; 
}