#ifndef ISTORE_H
#define ISTORE_H

#include <iostream>
#include "JVMinstruction.h"
#include "JVMlineOfCode.h"

namespace toycalc {

  class ISTORE : public JVMinstruction, public JVMlineOfCode {
  public:
    int index;

    ISTORE(int);
    std::string toString();
  };

}

#endif
