#include <iostream>
#include "IF_ICMPGT.h"
#include "label.h"

namespace toycalc {

  IF_ICMPGT::IF_ICMPGT(label* lbl) { l = lbl; }
  std::string IF_ICMPGT::toString() {
    return "\tif_icmpgt " + l->toString();
  }

}
