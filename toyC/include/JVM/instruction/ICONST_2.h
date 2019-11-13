#ifndef ICONST_2_H
#define ICONST_2_H

#include <iostream>
#include "JVMinstruction.h"
#include "JVMlineOfCode.h"

namespace toycalc {

  class ICONST_2 : public JVMinstruction, public JVMlineOfCode {
  public:
    ICONST_2();
    std::string toString();
  };

}
#endif
