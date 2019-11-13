#include <iostream>
#include "PUTSTATIC.h"

namespace toycalc {

  PUTSTATIC::PUTSTATIC(std::string n, std::string t) {
    name = n; type = t; 
  }

  std::string PUTSTATIC::toString() {
    return "\tputstatic " + name +" "+ type;
  }
  
}
