#include <iostream>

#include "ASblockState.h"
#include "TCoutput.h"

namespace toycalc {

    ASblockState::ASblockState(ASvarDef* varDefs[], ASstatement* statements[], int v_num, int s_num) {
        for (int i = 0; i < v_num; i++) varDefList[i] = varDefs[i];
        for (int i = 0; i < s_num; i++) statementList[i] = statements[i];
        numVarDefs = v_num;
        numStatements = s_num;
    }

    ASvarDef* ASblockState::getVarDefs(int n) { return varDefList[n]; }
    ASstatement* ASblockState::getStatements(int n) { return statementList[n]; }
    int ASblockState::getNumVarDefs() { return numVarDefs; }
    int ASblockState::getNumStatements() { return numStatements; }

    std::string ASblockState::toString() {
        if(numVarDefs==0 && numStatements==0) return "blockState([])";
        std::string s = "blockState(\n";
        indent();       //for varDefs
        s += spaces() + "[\n";
        indent();
        if (numVarDefs > 0) {

        }
        outdent();
        s += "\n" + spaces() + "]\n";

        indent();       //for statements
        s += spaces() + "[\n";
        indent();
        if (numStatements > 0) {

        }
        outdent();
        s += "\n" + spaces() + "]\n";

        outdent();
        s += spaces() + ")\n";
        return s;
    }
}