#ifndef ASNEWLINESTATE_H
#define ASNEWLINESTATE_H

#include "ASstatement.h"

namespace toycalc {

    class ASnewLineState:public ASstatement {
    public:
        ASnewLineState();
        std::string toString();
    };

}
#endif
