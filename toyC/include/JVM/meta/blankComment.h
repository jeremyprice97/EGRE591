#ifndef BLANKCOMMENT_H
#define BLANKCOMMENT_H

#include "JVMlineOfCode.h"
#include "JVMmeta.h"

namespace toycalc {
  
  class blankComment: public JVMmeta, public JVMlineOfCode {
    std::string toString();
  };

}

#endif
