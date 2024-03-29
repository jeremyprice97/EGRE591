#ifndef POP_H
#define POP_H

#include <iostream>
#include "JVMinstruction.h"
#include "JVMlineOfCode.h"

namespace toycalc {

  class POP : public JVMinstruction, public JVMlineOfCode {
  public:
    POP();
    std::string toString();
  };

}

#endif
