#ifndef ASWRITESTATE_H
#define ASWRITESTATE_H

#include "ASstatement.h"
#include "ASexpr.h"

namespace toycalc {
  
  class ASwriteState:public ASstatement {
  public:
    ASwriteState(ASexpr*);
    ASexpr *getExpression();
    std::string toString();
  private:
    ASexpr *expression;
  };
 
}
#endif
