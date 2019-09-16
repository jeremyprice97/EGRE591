#ifndef ASGOTOSTATE_H
#define ASGOTOSTATE_H

#include "ASstatement.h"

namespace toycalc {
  
  class ASgotoState:public ASstatement {
  public:
    ASgotoState(int);
    std::string toString();
    int getLabel();
  private:
    int label;
  };
 
}
#endif
