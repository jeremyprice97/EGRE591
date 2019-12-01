#include <iostream>
#include "JVMinstruction.h"
#include "JVMlineOfCode.h"
#include "IXOR.h"

namespace toycalc {

   // class IXOR : public JVMinstruction, JVMlineOfCode {
    //public:

        IXOR::IXOR() { }
        std::string IXOR::toString() {
            return "\tixor";
        }
    //};

}
