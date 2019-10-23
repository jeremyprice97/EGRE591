#include <iostream>

#include "ASnot.h"

namespace toycalc {

    ASnot::ASnot(ASexpression* e) { expression = e; setType(NoT);}

    ASexpression* ASnot::getExpression() { return expression; }

    std::string ASnot::toString() {
        return "not("+expression->toString()+")";
    }

}
