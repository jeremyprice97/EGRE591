#include <iostream>

#include "ASexprState.h"

namespace toycalc {

    ASexprState::ASexprState(ASexpression* e) {
        expression = e; setType(exprSstate);
    }
    ASexpression *ASexpressionState::getExpression() { return expression; }

    std::string ASexprState::toString() {
        return "exprState("+expression->toString()+")";
    }

}
