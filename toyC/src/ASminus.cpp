#include <iostream>

#include "ASminus.h"

namespace toycalc {

    ASminus::ASminus(ASexpression* e) { expression = e; }

    ASexpression* ASminus::getExpression() { return expression; }

    std::string ASminus::toString() {
        return "minus("+expression->toString()+")";
    }

}
