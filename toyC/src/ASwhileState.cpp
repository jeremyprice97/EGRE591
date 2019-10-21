#include <iostream>

#include "ASwhileState.h"

namespace toycalc {
    ASwhileState::ASwhileState(ASexpression* exp, ASstatement* state){
        expression = exp;  statement = state;
    }

    std::string ASwhileState::toString() {
        std::string s = "whileState(";
        s += expression->toString() + "," + statement->toString();
        s += ")";
        return s;
    }

    ASexpression* ASwhileState::getExpression() { return expression; }
    ASstatement* ASwhileState::getStatement() { return statement; }

}
