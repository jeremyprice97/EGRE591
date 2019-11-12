#include <iostream>
#include "INVOKEVIRTUAL.h"

namespace toycalc {

  INVOKEVIRTUAL::INVOKEVIRTUAL(std::string fc) { functionCall = fc; }
  std::string INVOKEVIRTUAL::toString() {
      return "\tinvokevirtual " + functionCall;
  }

}

