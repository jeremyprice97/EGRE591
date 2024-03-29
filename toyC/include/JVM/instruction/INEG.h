#ifndef INEG_H
#define INEG_H

#include <iostream>
#include "JVMinstruction.h"
#include "JVMlineOfCode.h"

namespace toycalc {

  class INEG : public JVMinstruction, public JVMlineOfCode {
  public:

    INEG();
    std::string toString();
  };

}

#endif
