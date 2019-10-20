#ifndef ASPROGRAM_H
#define ASPROGRAM_H

#include "ASabstractSyntax.h"
//#include "ASstatement.h"

//#define MAX_STATEMENTS 500 // arbitrary

namespace toycalc {

    enum stateType {exprState, breakState, blockState, ifState, nullState, returnState,
                    whileState, readState, writeState, newLineState};
  
    class ASstatement:public ASabstractSyntax {
     public:
        virtual std::string toString() = 0;
        enum stateType getType();
        void setType(enum stateType);
        std::string toTypeString(enum stateType);
      //ASprogram(std::string,ASstatement*[],int);
      //std::string toString();

      //std::string getName();
      //ASstatement *getStatement(int);
      //int getNumStatements();

     private:
        enum stateType type;
      //ASstatement *statementList[MAX_STATEMENTS];
      //std::string name;
      //int numStatements;
    };
 
}
#endif
