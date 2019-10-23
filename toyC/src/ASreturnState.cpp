#include <iostream>

#include "ASreturnState.h"

namespace toycalc {
    ASreturnState::ASreturnState(ASexpression* exp){
        expression = exp; setType(returnState);
    }

    std::string ASreturnState::toString() {
        std::string s = "returnState(";
        if (expression != NULL) {
            s += expression->toString();
        }
        s += ")";
        return s;
    }

    ASexpression* ASreturnState::getExpression() { return expression; }

}
