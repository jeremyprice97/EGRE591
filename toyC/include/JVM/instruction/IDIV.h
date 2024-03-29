#ifndef IDIV_H
#define IDIV_H

#include <iostream>
#include "JVMinstruction.h"
#include "JVMlineOfCode.h"

namespace toycalc {

  class IDIV : public JVMinstruction, public JVMlineOfCode {
  public:

    IDIV() { }
    std::string toString() {
      return "\tidiv";
    }
  };

}


#endif
