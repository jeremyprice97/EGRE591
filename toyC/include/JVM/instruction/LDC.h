#ifndef LDC_H
#define LDC_H

#include <iostream>
#include "JVMinstruction.h"
#include "JVMlineOfCode.h"

namespace toycalc {

  class LDC : public JVMinstruction, public JVMlineOfCode {
  public:
    int ival;
    std::string sval;

    LDC(int);
    LDC(std::string);
    std::string toString();
  };

}
#endif
