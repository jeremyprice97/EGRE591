#ifndef ASWHILESTATE_H
#define ASWHILESTATE_H

#include "ASabstractSyntax.h"
#include "ASstatement.h"
#include "ASexpression.h"

namespace toycalc {

    class ASwhileState:public ASstatement {
    public:
        ASwhileState(ASexpression*,ASstatement*);
        std::string toString();

        ASexpression *getExpression();
        ASstatement *getStatement();

    private:
        ASexpression *expression;
        ASstatement *statement;
    };

}
#endif