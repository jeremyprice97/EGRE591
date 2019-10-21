#include <iostream>

#include "ASbreakState.h"

namespace toycalc {

    ASbreakState::ASbreakState() { setType(breakState); }

    std::string ASbreakState::toString() { return "break()";}

}