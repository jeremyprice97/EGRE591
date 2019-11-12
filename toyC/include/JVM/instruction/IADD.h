#ifndef IADD_H
#define IADD_H

#include <iostream>
#include "JVMinstruction.h"
#include "JVMlineOfCode.h"

namespace toycalc {

  class IADD : public JVMinstruction, public JVMlineOfCode {
  public:

    IADD();
    std::string toString();
  };

}

#endif
