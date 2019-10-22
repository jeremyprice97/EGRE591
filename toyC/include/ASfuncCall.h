#ifndef ASFUNCCALL_H
#define ASFUNCCALL_H

//#include "ASabstractSyntax.h"
#include "ASexpression.h"

#define MAX_STATEMENTS 500 // arbitrary

namespace toycalc {

    class ASfuncCall:public ASexpression {
    public:
        ASfuncCall(int,ASexpression*[],int);
        std::string toString();

        int getID();
        ASexpression *getExpression(int);
        int getNumExpressions();

    private:
        ASexpression *expressionList[MAX_STATEMENTS];
        int ID;
        int numExpressions;
    };

}
#endif
