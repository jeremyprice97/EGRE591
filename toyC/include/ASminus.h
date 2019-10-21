#ifndef ASMINUSSTATE_H
#define ASMINUSSTATE_H

#include "ASexpression.h"

namespace toycalc {

    class ASminus:public ASexpression {
    public:
        ASminus(ASexpression*);
        ASexpression *getExpression();
        std::string toString();
    private:
        ASexpression *expression;
    };

}
#endif
