#include <iostream>

#include "ASoperator.h"
#include "TCtokens.h"

namespace toycalc {

    ASoperator::ASoperator(TCtoken* opr) { oper = opr; }

    std::string ASoperator::toString() {
        return ("operator("+oper->getLexeme()+")");
    }

    TCtoken* ASoperator::getOper() { return oper; }
}
