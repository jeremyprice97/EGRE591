#ifndef IOR_H
#define IOR_H

#include <iostream>
#include "JVMinstruction.h"
#include "JVMlineOfCode.h"

namespace toycalc {

  class IOR : public JVMinstruction, public JVMlineOfCode {
  public:

    IOR();
    std::string toString();
  };

}

#endif

