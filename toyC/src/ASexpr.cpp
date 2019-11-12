#include <iostream>
#include <string>
#include "ASexpr.h"
#include "TCoutput.h"

namespace toycalc {
    ASexpr::ASexpr(TCtoken* opr, ASexpression* oper1, ASexpression* oper2){
        oper = opr;  op1 = oper1; op2 = oper2; setType(expr);
    }

    std::string ASexpr::toString() {
        std::string s = "expr(\n";
        indent();
        s += spaces() + "[\n";
        indent();
        s += spaces() + oper->toString()+",\n"+
             spaces() + op1->toString()+",\n"+
             spaces() + op2->toString()+"\n";
        outdent();
        s += spaces() + "]\n";
        outdent();
        s += spaces() + ")";
        return s;

    }

    ASexpression* ASexpr::getOp1() { return op1; }
    ASexpression* ASexpr::getOp2() { return op2; }
    TCtoken* ASexpr::getOper() { return oper; }

}
