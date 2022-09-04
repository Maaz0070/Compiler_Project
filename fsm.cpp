#include "fsm.h"



int Fsm::nextState(int state, char input) {
    if(isalpha(input)) {
      if (islower(input)) {
        return transitionTable[state][0];
      } else {
        return transitionTable[state][1];
      }
    }
    if (isdigit(input)) {
      return transitionTable[state][2];
    }
    if ()
      return transitionTable[state][3];
    }

    
}

bool Fsm::isFinal(int state) {
    return false;
}
    
    
static bool isError(int state);
    static bool isValid(int state);
    static PascalTokens getToken(int state);
