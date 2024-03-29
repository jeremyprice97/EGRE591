#ifndef JVMCODEGENERATOR_H
#define JVMCODEGENERATOR_H

#include "CGcodeGenerator.h"
#include "ASabstractSyntax.h"
#include "JVMtargetCode.h"

namespace toycalc {
  
  class JVMcodeGenerator: public CGcodeGenerator{
  public:
    JVMcodeGenerator();
    CGtargetCode* generateCode(ASabstractSyntax *ast);
    JVMtargetCode *tc;
  };
 
}
#endif
