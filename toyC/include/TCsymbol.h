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
	int getOffset();
    void setOffset(int);
    static int getNextOffset();
    std::string toString();
    
  private:
    std::string id;
	int offset;
    enum symType type;
  };

}

#endif

