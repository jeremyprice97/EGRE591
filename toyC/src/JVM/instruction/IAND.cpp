#include <iostream>
#include "JVMinstruction.h"
#include "JVMlineOfCode.h"
#include "IAND.h"
namespace toycalc {

 // class IAND : public JVMinstruction, JVMlineOfCode {
  //public:

    IAND::IAND() { }
    std::string IAND::toString() {
      return "\tiand";
    }
  //};

}

