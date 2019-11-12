#include <iostream>
#include "ASTORE.h"

namespace toycalc {

  ASTORE::ASTORE(int i) { index = i; }
  std::string ASTORE::toString() {
    return "\tastore " + std::to_string(index);
  }

}

