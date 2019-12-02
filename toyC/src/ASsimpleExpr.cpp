#include <iostream>

#include "ASsimpleExpr.h"
#include "TCtokens.h"
#include "TCglobals.h"
#include "TCsymTable.h"

namespace toycalc {

    ASsimpleExpr::ASsimpleExpr(TCtoken* t) { expr = t; setType(simpleExpr);}
    TCsymbol* ASsimpleExpr::getId() { return symTable->getSym(expr); }
    std::string ASsimpleExpr::toString() {
		std::string str = "";
		str +=
			((expr->getTokenType()==NUMBER) ? ("(" + expr->getLexeme() + "," + "NUMBER)")  :
			(expr->getTokenType()==ID) ? symTable->getSym(expr)->toString() :
            (expr->getTokenType()==CHARLITERAL) ? ("(" + expr->getLexeme() + "," + "CHARLITERAL)") :
            (expr->getTokenType()==STRING) ? ("(" + expr->getLexeme() + "," + "STRING)") :
            "error"
            );
    return ("s_expr("+ str + ")");
    }

    TCtoken* ASsimpleExpr::getExpr() { return expr; }
}