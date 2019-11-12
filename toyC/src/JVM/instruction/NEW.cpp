#include <iostream>
#include "NEW.h"

namespace toycalc {

  NEW::NEW(std::string cn) { className = cn; }
  std::string NEW::toString() { return "\tnew " + className;  }

}

