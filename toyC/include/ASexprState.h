#ifndef ASWRITESTATE_H
#define ASWRITESTATE_H

#include "ASstatement.h"
#include "ASexpression.h"

namespace toycalc {

    class ASexprState:public ASstatement {
    public:
        ASexprState(ASexprssion*);
        ASexpression *getExpression();
        std::string toString();
    private:
        ASexpression *expression;
    };

}
#endif
