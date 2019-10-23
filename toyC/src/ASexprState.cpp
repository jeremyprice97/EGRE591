#include <iostream>

#include "ASexprState.h"

namespace toycalc {

    ASexprState::ASexprState(ASexpression* e) {
        expression = e; setType(exprState);
    }
    ASexpression *ASexprState::getExpression() { return expression; }

    std::string ASexprState::toString() {
		std::cout << "I'm in ASexprState!!\n";
		std::cout << expression->toString() << std::endl;
		std::cout << "I'm in still in ASexprState!!\n";
        return "exprState("+expression->toString()+")";
		std::cout << "I'm in ASexprState!! after!!!\n";
    }

}
