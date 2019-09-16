#include <iostream>

#include "ASsimpleExpr.h"
#include "TCtokens.h"
#include "TCglobals.h"

namespace toycalc {
  ASsimpleExpr::ASsimpleExpr(TCtoken* e){ expr = e; }

  std::string ASsimpleExpr::toString() {
    std::string str = "";
    str +=
      ((expr->getTokenType()==NUM) ? ("(" + expr->getLexeme() + "," + "NUM)")   :
       (expr->getTokenType()==ID) ? symTable->getSym(expr)->toString() :
       "error"
      );
    return ("s_expr("+ str + ")");
  }
  
  TCtoken* ASsimpleExpr::getExpr() { return expr; }
  
}
