#include <iostream>

#include "ASnewLineState.h"

namespace toycalc {

    ASnewLineState::ASnewLineState() { setType(newLineState); }

    std::string ASnewLineState::toString() { return "newLine()";}

}