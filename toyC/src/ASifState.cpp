#include <iostream>

#include "ASifState.h"

namespace toycalc {
    ASifState::ASifState(ASexpression* exp, ASstatement* state1, ASstatement* state2){
        expression = exp;  statement1 = state1; statement2 = state2; setType(ifState);
    }

    std::string ASifState::toString() {
        std::string s = "ifState(";
        s += expression->toString() + "," + statement1->toString();
        if (statement2 != NULL) {
            s += "," + statement2->toString();
        }
        s += ")";
        return s;
    }

    ASexpression* ASifState::getExpression() { return expression; }
    ASstatement* ASifState::getStatement1() { return statement1; }
    ASstatement* ASifState::getStatement2() { return statement2; }

}
