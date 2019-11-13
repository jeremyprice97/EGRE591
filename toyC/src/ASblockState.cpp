#include <iostream>

#include "ASblockState.h"
#include "TCoutput.h"
#include "ASexpression.h"
namespace toycalc {

    ASblockState::ASblockState(ASdefinition* varDefs[], ASstatement* statements[], int v_num, int s_num) {
        for (int i = 0; i < v_num; i++) varDefList[i] = varDefs[i];
        for (int i = 0; i < s_num; i++) statementList[i] = statements[i];
        numVarDefs = v_num;
        numStatements = s_num;
        setType(blockState);
    }

    ASdefinition* ASblockState::getVarDefs(int n) { return varDefList[n]; }
    ASstatement* ASblockState::getStatement(int n) { return statementList[n]; }
    int ASblockState::getNumVarDefs() { return numVarDefs; }
    int ASblockState::getNumStatements() { return numStatements; }

    std::string ASblockState::toString() {
        if(numVarDefs==0 && numStatements==0) return "blockState([])";
        std::string s = "blockState(\n";
	    indent();
        s += spaces() + "[\n";
        indent();
        if(numVarDefs > 0) {
            s += spaces() + varDefList[0]->toString();
            for (int i=1; i < numVarDefs; i++)
                s += ",\n"+spaces()+varDefList[i]->toString();
        }
        outdent();
        s += "\n" + spaces() + "],\n";

              //for statements
        s += spaces() + "[\n";
        indent();
        if (numStatements > 0) {
            s += spaces() + statementList[0]->toString();
            for (int i=1; i < numStatements; i++) {
                s += ",\n"+spaces()+statementList[i]->toString();
			}
        }
        outdent();
        s += "\n" + spaces() + "]\n";
        outdent();
		s += spaces();
		s += ")";
        return s;
    }
}