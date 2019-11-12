#ifndef CGCODEGENERATOR_H
#define CGCODEGENERATOR_H

#include "CGtargetCode.h"
#include "ASabstractSyntax.h"

namespace toycalc {
  
  class  CGcodeGenerator {
  public:
    virtual CGtargetCode *generateCode(ASabstractSyntax *ast) = 0;
  };

}
#endif
