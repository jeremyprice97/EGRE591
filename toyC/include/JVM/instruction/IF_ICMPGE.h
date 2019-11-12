#ifndef IF_ICMPGE_H
#define IF_ICMPGE_H

#include <iostream>
#include "JVMinstruction.h"
#include "JVMlineOfCode.h"
#include "label.h"

namespace toycalc {

  class IF_ICMPGE : public JVMinstruction, public JVMlineOfCode {
  public:
    label *l;

    IF_ICMPGE(label*);
    std::string toString();
  };

}

#endif

