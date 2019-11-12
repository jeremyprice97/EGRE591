#ifndef JVMGENERATEEXPRESSION_H
#define JVMGENERATEEXPRESSION_H

#include "ASexpr.h"
#include "JVMtargetCode.h"

namespace toycalc {

  class JVMgenerateExpression {
  public:
    static void genExpression(ASexpr*,JVMtargetCode*);
  };

}

#endif
