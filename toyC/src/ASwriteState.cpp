#include <iostream>

#include "ASwriteState.h"
#include "TCoutput.h"

namespace toycalc{

    ASwriteState::ASwriteState(ASexpression* expressions[], int num) {
        for (int i=0; i < num; i++) expressionList[i] = expressions[i];
        numExpressions = num;
        setType(writeState);
    }

    ASexpression* ASwriteState::getExpression(int n) { return expressionList[n]; }
    int ASwriteState::getNumExpressions() { return numExpressions; }

    std::string ASwriteState::toString() {
        if (numExpressions==0) return "writeState([])";
        std::string s = "writeState(\n";
        indent();
        s += spaces() + "[\n";
        indent();
        if (numExpressions > 0) {
            s += spaces() + expressionList[0]->toString();
            for (int i=1; i < numExpressions; i++)
                s += ",\n"+spaces()+expressionList[i]->toString();
        }
        outdent();
        s += "\n"+spaces() + "]\n";
        outdent();
        s += spaces() + ")\n";
        return s;
    }

}
