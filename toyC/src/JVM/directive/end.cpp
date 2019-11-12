#include <iostream>

#include "end.h"

namespace toycalc {

  end::end() { directive = ".end"; }
  std::string end::toString() { return (directive + " method"); }
  
}

