#include <iostream>

#include "ASskipState.h"

namespace toycalc {
  ASskipState::ASskipState() { setType(SKIPstate); }

  std::string ASskipState::toString() { return "skip()"; }

}
