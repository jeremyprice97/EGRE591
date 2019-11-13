#ifndef IMUL_H
#define IMUL_H

#include <iostream>
#include "JVMinstruction.h"
#include "JVMlineOfCode.h"

namespace toycalc {

  class IMUL : public JVMinstruction, public JVMlineOfCode {
  public:

    IMUL();
    std::string toString();
  };

}

#endif
