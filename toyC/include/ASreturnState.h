#ifndef ASRETURNSTATE_H
#define ASRETURNSTATE_H

#include "ASabstractSyntax.h"
#include "ASstatement.h"
#include "ASexpression.h"

namespace toycalc {

    class ASreturnState:public ASstatement {
    public:
        ASreturnState(ASexpression*);
        std::string toString();

        ASexpression *getExpression();

    private:
        ASexpression *expression;
    };

}
#endif