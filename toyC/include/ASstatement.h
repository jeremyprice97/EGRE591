#ifndef ASPROGRAM_H
#define ASPROGRAM_H

#include "ASabstractSyntax.h"

namespace toycalc {

    enum stateType {exprState, breakState, blockState, ifState, nullState, returnState,
                    whileState, readState, writeState, newLineState};
  
    class ASstatement:public ASabstractSyntax {
     public:
        virtual std::string toString() = 0;
        enum stateType getType();
        void setType(enum stateType);
        std::string toTypeString(enum stateType);

     private:
        enum stateType type;

    };
 
}
#endif
