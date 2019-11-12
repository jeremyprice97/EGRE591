#ifndef ALOAD_2_H
#define ALOAD_2_H

#include <iostream>
#include "JVMinstruction.h"
#include "JVMlineOfCode.h"

namespace toycalc {

  class ALOAD_2 : public JVMinstruction, public JVMlineOfCode {
  public:
    ALOAD_2();
    std::string toString();
  };

}

#endif
