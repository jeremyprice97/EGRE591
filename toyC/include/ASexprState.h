#ifndef ASEXPRSTATE_H
#define ASEXPRSTATE_H

#include "ASstatement.h"
#include "ASexpression.h"

namespace toycalc {

    class ASexprState:public ASstatement {
    public:
        ASexprState(ASexpression*);
        ASexpression* getExpression();
        std::string toString();
    private:
        ASexpression *expression;
    };

}
#endif
