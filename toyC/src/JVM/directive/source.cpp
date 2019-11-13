#include <iostream>

#include "source.h"

namespace toycalc {

  source::source(std::string s) {
    directive = ".source";
    fileName = s;
  }
  
  std::string source::toString() {
    return (directive+ " " + fileName);
  }

}
