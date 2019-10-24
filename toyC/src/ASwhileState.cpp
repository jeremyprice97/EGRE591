#include <iostream>

#include "ASwhileState.h"
#include "TCoutput.h"

namespace toycalc {
    ASwhileState::ASwhileState(ASexpression* exp, ASstatement* state){
        expression = exp;  statement = state; setType(whileState);
    }

    std::string ASwhileState::toString() {
        std::string s = "whileState(\n";
        indent();
        s += spaces() + "[\n";
        indent();
        s += spaces() + expression->toString();
        s += ",\n" + spaces() + statement->toString();
        outdent();
        s += "\n" + spaces() + "]\n";
        outdent();
		s += spaces();
        s +=  ")";
        return s;
    }

    ASexpression* ASwhileState::getExpression() { return expression; }
    ASstatement* ASwhileState::getStatement() { return statement; }

}
