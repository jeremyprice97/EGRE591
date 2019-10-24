#include <iostream>

#include "ASexprState.h"
#include "TCoutput.h"

namespace toycalc {

    ASexprState::ASexprState(ASexpression* e) {
        expression = e; setType(exprState);
    }
    ASexpression *ASexprState::getExpression() { return expression; }

    std::string ASexprState::toString() {
        std::string s = "exprState(\n";
        indent();
        s += spaces() + "[\n";
        indent();
        s += spaces() + expression->toString();
        outdent();
        s += "\n" + spaces() + "]\n";
        outdent();
        s += spaces() + ")";
        return s;
        //return "exprState("+expression->toString()+")";
    }

}
