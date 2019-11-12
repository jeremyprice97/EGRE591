#ifndef ILOAD_H
#define ILOAD_H

#include <iostream>
#include "JVMinstruction.h"
#include "JVMlineOfCode.h"

namespace toycalc {

  class ILOAD : public JVMinstruction, public JVMlineOfCode {
  public:
    int index;
    ILOAD(int);
    std::string toString();
  };

}

#endif
