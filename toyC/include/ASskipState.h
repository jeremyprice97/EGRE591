#ifndef ASSKIPSTATE_H
#define ASSKIPSTATE_H

#include "ASstatement.h"

namespace toycalc {
  
  class ASskipState:public ASstatement {
  public:
    ASskipState();
    std::string toString();
  };
 
}
#endif
