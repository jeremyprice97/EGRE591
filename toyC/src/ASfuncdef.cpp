#include <iostream>

#include "ASfuncDef.h"
#include "TCoutput.h"
#include "TCtokens.h"
#include "TCglobals.h"
namespace toycalc{

    ASfuncDef::ASfuncDef(int l, TCtoken* t, ASdefinition* varDefs[], ASstatement* state, int v_num) {
        ID = l; type = t; statement = state; numVarDefs = v_num;
        setType(funcDef);
        for (int i = 0; i < v_num; i++) varDefsList[i] = varDefs[i];
    }

    int ASfuncDef::getID() { return ID; }
    TCtoken* ASfuncDef::getToken() { return type; }
    ASdefinition* ASfuncDef::getVarDefs(int n) { return varDefsList[n]; }
    ASstatement* ASfuncDef::getStatement() { return statement; }
    int ASfuncDef::getNumVarDefs() { return numVarDefs; }

    std::string ASfuncDef::toString() {
        std::string s = "funcDef(\n";
		indent();
        s += spaces() + symTable->getSym(ID)->toString() + ",\n";
        s += spaces() + type->toString() + ",\n";
		s += spaces()+"(\n";
		indent();
        s += spaces() + "[\n";
        indent();
        if(numVarDefs > 0) {
            s += spaces()+varDefsList[0]->toString();
            for (int i=1; i < numVarDefs; i++)
                s += ",\n"+spaces()+varDefsList[i]->toString();
        }
        outdent();
        s += "\n"+spaces() + "],\n";
        outdent();
        s += spaces() + statement->toString();
        outdent();
		s += "\n"+spaces()+")";
        return s;
    }

}
