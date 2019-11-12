#ifndef NEW_H
#define NEW_H

#include <iostream>
#include "JVMinstruction.h"
#include "JVMlineOfCode.h"

namespace toycalc {

  class NEW : public JVMinstruction, public JVMlineOfCode {
  public:
    std::string className;

    NEW(std::string);
    std::string toString();
  };

}

#endif
