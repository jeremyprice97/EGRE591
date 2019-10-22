#include <iostream>

#include "ASfuncDef.h"
#include "TCoutput.h"
#include "TCtokens.h"

namespace toycalc{

    ASfuncDef::ASfuncDef(int l, TCtoken* t, ASdefinition* varDefs[], ASstatement* state, int v_num) {
        ID = l; type = t; statement = state; numVarDefs = v_num;
        for (int i = 0; i < v_num; i++) varDefsList[i] = varDefs[i];
    }

    int ASfuncDef::getID() { return ID; }
    TCtoken* ASfuncDef::getToken() { return type; }
    ASdefinition* ASfuncDef::getVarDefs(int n) { return varDefsList[n]; }
    ASstatement* ASfuncDef::getStatement() { return statement; }
    int ASfuncDef::getNumVarDefs() { return numVarDefs; }

    std::string ASfuncDef::toString() {
        std::string s = "funcDef(\n";
        s += ID + ",";
        s += type->toString() + ",";
        indent();
        s += spaces() + "[\n";
        indent();
        if(numVarDefs > 0) {
            s += varDefsList[0]->toString();
            for (int i=1; i < numVarDefs; i++)
                s += ",\n"+spaces()+varDefsList[i]->toString();
        }
        outdent();
        s += "\n"+spaces() + "]\n";
        outdent();
        s += "," + statement->toString();
        s += ")\n";
        return s;
    }

}
