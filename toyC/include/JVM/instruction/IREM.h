#ifndef IREM_H
#define IREM_H

#include <iostream>
#include "JVMinstruction.h"
#include "JVMlineOfCode.h"

namespace toycalc {

  class IREM : public JVMinstruction, public JVMlineOfCode {
  public:

    IREM();
    std::string toString();
  };

}

#endif

