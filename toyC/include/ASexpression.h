#ifndef ASEXPRESSION_H
#define ASEXPRESSION_H

#include "ASabstractSyntax.h"

namespace toycalc {

    class ASexpression:public ASabstractSyntax{
    public:
        virtual std::string toString() = 0;
    };

}
#endif