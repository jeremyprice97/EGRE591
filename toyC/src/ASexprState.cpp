#include <iostream>

#include "ASexprState.h"

namespace toycalc {

    ASexprState::ASexprState(ASexpression* e) {
        expression = e; setType(exprState);
    }
    ASexpression *ASexprState::getExpression() { return expression; }

    std::string ASexprState::toString() {
        return "exprState("+expression->toString()+")";
    }

}
