#ifndef ASSIMPLEEXPR_H
#define ASSIMPLEEXPR_H

#include "ASexpression.h"
#include "TCtoken.h"

namespace toycalc {

    class ASsimpleExpr:public ASexpression {
    public:
        ASsimpleExpr(TCtoken *);
        std::string toString();
        TCtoken* getExpr();

    private:
        TCtoken *expr;
    };
}

#endif
