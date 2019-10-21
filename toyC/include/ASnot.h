#ifndef ASNOTSTATE_H
#define ASNOTSTATE_H

#include "ASexpression.h"

namespace toycalc {

    class ASnot:public ASexpression {
    public:
        ASnot(ASexpression*);
        ASexpression *getExpression();
        std::string toString();
    private:
        ASexpression *expression;
    };

}
#endif
