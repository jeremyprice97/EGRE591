#include <iostream>
#include "JVMinstruction.h"
#include "JVMlineOfCode.h"

namespace toycalc {

  class IDIV : public JVMinstruction, JVMlineOfCode {
  public:

    IDIV() { }
    std::string toString() {
      return "\tidiv";
    }
  };

}

