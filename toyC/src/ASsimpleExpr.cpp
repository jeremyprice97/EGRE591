#include <iostream>

#include "ASsimpleExpr.h"
#include "TCtokens.h"
#include "TCglobals.h"

namespace toycalc {

    ASsimpleExpr::ASsimpleExpr(TCtoken* t) { expr = t; }

    std::string ASsimpleExpr::toString() {
        std::string str = "";
        if(expr->getTokenType() == NUMBER)
            str += ("(" + expr->getLexeme() + "," + "NUMBER)");
        else if(expr->getTokenType() == ID)
            str += symTable->getSym(expr)->toString();
        else
            str += "error";
        return ("s_expr("+ str + ")");
    }
    TCtoken* ASsimpleExpr::getExpr() { return expr; }
}