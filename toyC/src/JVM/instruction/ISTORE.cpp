#include <iostream>
#include "ISTORE.h"

namespace toycalc {

  ISTORE::ISTORE(int i) { index = i; }
  std::string ISTORE::toString() {
    return "\tistore " + std::to_string(index);
  }

}
