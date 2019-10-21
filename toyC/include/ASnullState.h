#ifndef ASNULLSTATE_H
#define ASNULLSTATE_H

#include "ASstatement.h"

namespace toycalc {

    class ASnullState:public ASstatement {
    public:
        ASnullState();
        std::string toString();
    };

}
#endif
