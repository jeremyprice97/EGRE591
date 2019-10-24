#include <iostream>

#include "ASifState.h"
#include "TCoutput.h"

namespace toycalc {
    ASifState::ASifState(ASexpression* exp, ASstatement* state1, ASstatement* state2){
        expression = exp;  statement1 = state1; statement2 = state2; setType(ifState);
    }

    std::string ASifState::toString() {
        std::string s = "ifState(\n";
        indent();
        s += spaces() + "[\n";
        indent();
        s += spaces() + expression->toString() + ",\n";
        s += spaces() + statement1->toString();
        if (statement2 != NULL) {
            s += ",\n" + spaces() + statement2->toString();
        }
        outdent();
        s += "\n" + spaces() + "]\n";
        outdent();
        s += spaces() + ")";
        return s;
    }

    ASexpression* ASifState::getExpression() { return expression; }
    ASstatement* ASifState::getStatement1() { return statement1; }
    ASstatement* ASifState::getStatement2() { return statement2; }

}
