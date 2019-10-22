#ifndef ASOPERATOR_H
#define ASOPERATOR_H

#include "ASabstractSyntax.h"
#include "TCtoken.h"

namespace toycalc {

    class ASoperator:public ASabstractSyntax {
    public:
        ASoperator(TCtoken*);
        std::string toString();
        TCtoken *getOper();

    private:
        TCtoken *oper;
    };

}

#endif
