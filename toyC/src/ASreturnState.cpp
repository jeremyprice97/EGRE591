#include <iostream>

#include "ASreturnState.h"

namespace toycalc {
    ASreturnState::ASreturnState(ASexpression* exp){
        expression = exp;
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
