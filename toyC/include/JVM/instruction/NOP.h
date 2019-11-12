#ifndef NOP_H
#define NOP_H

#include <iostream>
#include "JVMinstruction.h"
#include "JVMlineOfCode.h"

namespace toycalc {

  class NOP : public JVMinstruction, public JVMlineOfCode {
  public:
    NOP();
    std::string toString();
  };

}

#endif
