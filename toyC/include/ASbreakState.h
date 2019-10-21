#ifndef ASBREAKSTATE_H
#define ASBREAKSTATE_H

#include "ASstatement.h"

namespace toycalc {

    class ASbreakState:public ASstatement {
    public:
        ASbreakState();
        std::string toString();
    };

}
#endif
