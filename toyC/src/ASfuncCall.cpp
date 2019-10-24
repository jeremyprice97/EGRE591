#include <iostream>

#include "ASfuncCall.h"
#include "TCoutput.h"
#include "TCglobals.h"
namespace toycalc{

    ASfuncCall::ASfuncCall(int l, ASexpression* expressions[], int num) {
        for (int i=0; i < num; i++) expressionList[i] = expressions[i];
        ID = l; numExpressions = num; setType(funcCall);
    }

    int ASfuncCall::getID() { return ID; }
    ASexpression* ASfuncCall::getExpression(int n) { return expressionList[n]; }
    int ASfuncCall::getNumExpressions() { return numExpressions; }

    std::string ASfuncCall::toString() {
        if (numExpressions==0) return "funcCall("+ symTable->getSym(ID)->toString() + std::string(")");
        std::string s = "funcCall(\n";
        indent();
        s += spaces();
        s += symTable->getSym(ID)->toString();          ///////issue here with ID
        s += ",\n";
        s += spaces() + "[\n";
        indent();
        if (numExpressions > 0) {
            s += (spaces()+expressionList[0]->toString());
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
