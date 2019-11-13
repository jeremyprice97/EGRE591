#ifndef TIMEANDSOURCECOMMENT_H
#define TIMEANDSOURCECOMMENT_H

#include "JVMlineOfCode.h"
#include "JVMmeta.h"

namespace toycalc {
  class timeAndSourceComment: public JVMmeta, public JVMlineOfCode{
  public:
    std::string text;

    timeAndSourceComment(std::string);
    timeAndSourceComment();
    std::string toString();
  };
}

#endif
