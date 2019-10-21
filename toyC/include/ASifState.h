#ifndef ASIFSTATE_H
#define ASIFSTATE_H

#include "ASabstractSyntax.h"
#include "ASstatement.h"
#include "ASexpression.h"

namespace toycalc {

    class ASifState:public ASstatement {
    public:
        ASifState(ASexpression*,ASstatement*,ASstatement*);
        std::string toString();

        ASexpression *getExpression();
        ASstatement *getStatement1();
        ASstatement *getStatement2();

    private:
        ASexpression *expression;
        ASstatement *statement1, *statement2;
    };

}
#endif