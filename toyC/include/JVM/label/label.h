#ifndef LABEL_H
#define LABEL_H

#include <iostream>
#include "JVMlineOfCode.h"
#include "JVMlabel.h"

namespace toycalc {

  class label : public JVMlineOfCode, JVMlabel {
  public:
    std::string l;

    label();
    label(std::string);
    std::string getLabel();
    std::string toString();
  };

}

#endif

