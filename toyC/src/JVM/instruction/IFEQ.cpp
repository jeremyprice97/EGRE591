#include <iostream>
#include "IFEQ.h"
#include "label.h"

namespace toycalc {

  IFEQ::IFEQ(label* lbl) { l = lbl; }
  std::string IFEQ::toString() {
    return "\tifeq " + l->toString();
  }

}
