#include <iostream>
#include "JVMinstruction.h"
#include "JVMlineOfCode.h"

namespace toycalc {

  class IRETURN : public JVMinstruction, JVMlineOfCode {
  public:

    IRETURN() { }
    std::string toString() {
      return "\tireturn";
    }
  };

}

