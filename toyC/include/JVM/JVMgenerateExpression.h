#ifndef JVMGENERATEEXPRESSION_H
#define JVMGENERATEEXPRESSION_H

#include "ASexpression.h"
#include "JVMtargetCode.h"

namespace toycalc {

  class JVMgenerateExpression {
  public:
    static void genExpression(ASexpression*,JVMtargetCode*);
  };

}

#endif
