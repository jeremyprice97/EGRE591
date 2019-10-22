#include <iostream>

#ifndef TCSYMBOL_H
#define TCSYMBOL_H
/*Provided by Dr. Resler*/

namespace toycalc {

  enum symType { VAR, FUNC, OFFSET, NO_TYPE };
    
  class TCsymbol {
  public:
    TCsymbol();
    TCsymbol(std::string, enum symType);
    
    std::string getId();
    void setId(std::string);
    enum symType getType();
    void setType(enum symType);
    std::string toString();
    
  private:
    std::string id;
    enum symType type;
  };

}

#endif

