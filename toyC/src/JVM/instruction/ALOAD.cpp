#include <iostream>
#include "ALOAD.h"

namespace toycalc {

  ALOAD::ALOAD(int i) { index = i; }
  std::string ALOAD::toString() {
    return "\taload " + std::to_string(index);
  }

}
