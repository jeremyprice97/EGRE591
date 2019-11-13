#ifndef DUP_H
#define DUP_H

#include <iostream>
#include "JVMinstruction.h"
#include "JVMlineOfCode.h"

namespace toycalc {

  class DUP : public JVMinstruction, public JVMlineOfCode {
  public:
    DUP();
    std::string toString();
  };

}

#endif
