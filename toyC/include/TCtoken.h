#ifndef TCTOKEN_H
#define TCTOKEN_H
/*Provided by Dr. Resler*/

namespace toycalc {
  class TCtoken{
  public:
    TCtoken();
    TCtoken(int);
    TCtoken(int,std::string);
    int getTokenType();
    std::string getLexeme();
    std::string toString();

  private:
    int tokenType;
    std::string lexeme;
  };

}
#endif
