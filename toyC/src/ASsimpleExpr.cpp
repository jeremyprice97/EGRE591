#include <iostream>

#include "ASsimpleExpr.h"
#include "TCtokens.h"
#include "TCglobals.h"

namespace toycalc {

    ASsimpleExpr::ASsimpleExpr(TCtoken* t) { expr = t; setType(simpleExpr);}
	std::string ASsimpleExpr::toString() {
		std::cout << "I'm in ASsimpleExpr!! before?!!!\n";
		std::string str = "";
		str +=
			((expr->getTokenType()==NUMBER) ? ("(" + expr->getLexeme() + "," + "NUMBER)")   :
			(expr->getTokenType()==ID) ? symTable->getSym(expr)->toString() :
       "error"
      );
    return ("s_expr("+ str + ")");
  }
    /*std::string ASsimpleExpr::toString() {
		std::cout << "I'm in ASsimpleExpr!! before?!!!\n";
        std::string str = "";
        if(expr->getTokenType() == NUMBER)
            str += ("(" + expr->getLexeme() + "," + "NUMBER)");
        else if(expr->getTokenType() == ID) {
			std::cout << "I'm in ASsimpleExpr!! before?!!!\n";
            str += symTable->getSym(expr)->toString();
		}
        else
            str += "error";
        return ("s_expr("+ str + ")");
    }
	*/
    TCtoken* ASsimpleExpr::getExpr() { return expr; }
}