#ifndef IAND_H
#define IAND_H

#include <iostream>
#include "JVMinstruction.h"
#include "JVMlineOfCode.h"

namespace toycalc {

  class IAND : public JVMinstruction, public JVMlineOfCode {
  public:

    IAND();
    std::string toString();
  };

}

#endif


