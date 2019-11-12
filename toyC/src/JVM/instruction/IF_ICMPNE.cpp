#include <iostream>
#include "IF_ICMPNE.h"
#include "label.h"

namespace toycalc {

  IF_ICMPNE::IF_ICMPNE(label* lbl) { l = lbl; }
  std::string IF_ICMPNE::toString() {
    return "\tif_icmpne " + l->toString();
  }

}
