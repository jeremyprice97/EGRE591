#include <iostream>

#include "ASnullState.h"

namespace toycalc {

    ASnullState::ASnullState() { setType(nullState); }

    std::string ASnullState::toString() { return "null()";}

}