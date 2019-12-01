#include <iostream>
#include "JVMinstruction.h"
#include "JVMlineOfCode.h"
#include "IREM.h"
namespace toycalc {

  //class IREM : public JVMinstruction, JVMlineOfCode {
  //public:

    IREM::IREM() { }
    std::string IREM::toString() {
      return "\tirem";
    }
  //};

}

