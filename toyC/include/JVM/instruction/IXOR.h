#ifndef IXOR_H
#define IXOR_H

#include <iostream>
#include "JVMinstruction.h"
#include "JVMlineOfCode.h"

namespace toycalc {

    class IXOR : public JVMinstruction, public JVMlineOfCode {
    public:

        IXOR();
        std::string toString();
    };

}

#endif

