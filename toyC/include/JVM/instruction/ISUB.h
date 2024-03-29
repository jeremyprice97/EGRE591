#ifndef ISUB_H
#define ISUB_H

#include <iostream>
#include "JVMinstruction.h"
#include "JVMlineOfCode.h"

namespace toycalc {

  class ISUB : public JVMinstruction, public JVMlineOfCode {
  public:
    ISUB();
    std::string toString();
  };

}

#endif
