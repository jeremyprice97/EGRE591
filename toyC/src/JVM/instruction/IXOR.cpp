#include <iostream>
#include "JVMinstruction.h"
#include "JVMlineOfCode.h"

namespace toycalc {

    class IXOR : public JVMinstruction, JVMlineOfCode {
    public:

        IXOR() { }
        std::string toString() {
            return "\tixor";
        }
    };

}
