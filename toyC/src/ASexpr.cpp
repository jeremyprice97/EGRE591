#include <iostream>

#include "ASexpr.h"

namespace toycalc {
    ASexpr::ASexpr(TCtoken* opr, ASexpression* oper1, ASexpression* oper2){
        oper = opr;  op1 = oper1; op2 = oper2;
    }

    std::string ASexpr::toString() {
        return ("expr("+oper->getLexeme()+","+
                op1->toString()+","+
                op2->toString()+")");

    }

    ASexpression* ASexpr::getOp1() { return op1; }
    ASexpression* ASexpr::getOp2() { return op2; }
    TCtoken* ASexpr::getOper() { return oper; }

}
