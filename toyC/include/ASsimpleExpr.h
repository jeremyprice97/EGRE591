#ifndef ASSIMPLEEXPR_H
#define ASSIMPLEEXPR_H

#include "ASexpression.h"
#include "TCtoken.h"
#include "TCsymbol.h"

namespace toycalc {

    class ASsimpleExpr:public ASexpression {
    public:
        ASsimpleExpr(TCtoken *);
        std::string toString();
        TCtoken* getExpr();
        TCsymbol* getId();

    private:
        TCtoken *expr;
    };
}

#endif
