#include <iostream>
#include "JVMinstruction.h"
#include "JVMlineOfCode.h"

namespace toycalc {

  class IAND : public JVMinstruction, JVMlineOfCode {
  public:

    IAND() { }
    std::string toString() {
      return "\tiand";
    }
  };

}

