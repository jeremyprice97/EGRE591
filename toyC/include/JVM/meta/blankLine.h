#ifndef BLANKLINE_H
#define BLANKLINE_H

#include "JVMmeta.h"
#include "JVMlineOfCode.h"

namespace toycalc {
  
class blankLine: public JVMmeta, public JVMlineOfCode{
 public:
  std::string toString();
};

}

#endif

