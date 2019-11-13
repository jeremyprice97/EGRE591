#include <iostream>
#include "JVMinstruction.h"
#include "JVMlineOfCode.h"

namespace toycalc {

  class IOR : public JVMinstruction, JVMlineOfCode {
  public:

    IOR() { }
    std::string toString() {
      return "\tior";
    }
  };

}

