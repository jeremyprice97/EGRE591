#include <iostream>
#include "JVMinstruction.h"
#include "JVMlineOfCode.h"

namespace toycalc {

  class IREM : public JVMinstruction, JVMlineOfCode {
  public:

    IREM() { }
    std::string toString() {
      return "\tirem";
    }
  };

}

