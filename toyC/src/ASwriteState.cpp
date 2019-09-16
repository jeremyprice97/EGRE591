#include <iostream>

#include "ASwriteState.h"

namespace toycalc {

  ASwriteState::ASwriteState(ASexpr* e) {
    expression = e; setType(WRITEstate);
  }
  ASexpr *ASwriteState::getExpression() { return expression; }

  std::string ASwriteState::toString() {
    return "write("+expression->toString()+")";
  }

}
