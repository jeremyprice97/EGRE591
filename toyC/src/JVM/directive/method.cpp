#include <iostream>

#include "method.h"

namespace toycalc {

  method::method(std::string n, std::string t) {
    directive = ".method";
    accessSize = 0; argsSize = 0; name = n; type = t;
  }

  void method::addAccessSpec(std::string s) { accessSpecs[accessSize++] = s; }
  void method::addArg(std::string s) { args[argsSize++] = s; }
  void method::addArg(int numVars) {
      for(argsSize = 0; argsSize < numVars; argsSize++) {
          args[argsSize] = "I";
      }
  }
  std::string method::toString() {
    std::string s = directive + " ";
    for (int i=0; i<accessSize; i++) s += (accessSpecs[i] + " ");
    s += name + "(";
    for (int i=0; i<argsSize; i++) s += args[i];
    s += (")" + type);
    return s;
  }
  
}

