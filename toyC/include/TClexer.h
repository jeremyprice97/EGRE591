#ifndef TCLEXER_H
#define TCLEXER_H

#include "TCtoken.h"
/*Provided by Dr. Resler*/

namespace toycalc {

  class TClexer {
  public:
  TClexer(std::string);
  TCtoken* getToken();

  std::string getLine();
  std::string getLexeme();
  int getLineNum();
  int getPos();
  };
 
}
#endif
