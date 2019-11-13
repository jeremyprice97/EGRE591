#include <iostream>

#include "throws_.h"

namespace toycalc {

  throws_::throws_(std::string s) {
    directive = ".throws";
    exception = s;
  }
  std::string throws_::toString() {
    std::string s = "\t" + directive + " " + exception;
    return s;
  }
  
}
