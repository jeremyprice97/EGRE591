#include "TCsymbol.h"
/*Provided by Dr. Resler*/

namespace toycalc {

  int _nextOffset = 1;
	
  TCsymbol::TCsymbol() { id = ""; type = NO_TYPE; }
  TCsymbol::TCsymbol(std::string str, enum symType t) {
    id = str; type = t;
  }

  std::string TCsymbol::getId() { return id; }
  void TCsymbol::setId(std::string str) { id = str; }
  enum symType TCsymbol::getType() { return type; }
  void TCsymbol::setType(enum symType t) { type = t; }
  int TCsymbol::getOffset() { return offset; }
  void TCsymbol::setOffset(int n) { offset = n; }
  int TCsymbol::getNextOffset() { return _nextOffset++; }

  std::string TCsymbol::toString() {
    std::string str="(";
    str += (getId()+",");
    switch(getType()) {
    case VAR:     str += "VAR";     break;
    case FUNC:   str += "FUNC";   break;
    case NO_TYPE: str += "NO_TYPE"; break;
    default:      str += "ERROR";   break;
    }
    str += ")";
    return str;
  }
}
