#ifndef ASWRITESTATE_H
#define ASWRITESTATE_H

#include "ASstatement.h"
#include "ASexpression.h"

#define MAX_STATEMENTS 500 // arbitrary

namespace toycalc {

    class ASwriteState : public ASstatement {
    public:
        ASwriteState(ASexpression *[], int);

        std::string toString();

        ASexpression *getExpression(int);

        int getNumExpressions();

    private:
        ASexpression *expressionList[MAX_STATEMENTS];
        int numExpressions;
    };
}
#endif