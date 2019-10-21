#ifndef ASEXPR_H
#define ASEXPR_H

#include "ASexpression.h"
#include "TCtoken.h"

namespace toycalc {

    class ASexpr:public ASexpression{
    public:
        ASexpr(TCtoken*,ASexpression*,ASexpression*);
        std::string toString();
        ASexpression* getOp1();
        ASexpression* getOp2();
        TCtoken* getOper();

    private:
        TCtoken *oper;
        ASexpression *op1,*op2;

    };

}
#endif
