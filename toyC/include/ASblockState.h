#ifndef ASBLOCKSTATE_H
#define ASBLOCKSTATE_H

#include "ASabstractSyntax.h"
#include "ASstatement.h"
#include "ASvarDef.h"

#define MAX 500

namespace toycalc {

    class ASblockState:public ASabstractSyntax {
    public:
        ASblockState(ASvarDef*[],ASstatement*[],int,int);
        std::string toString();

        ASvarDef *getVarDefs(int);
        ASstatement *getStatements(int);
        int getNumVarDefs();
        int getNumStatements();

    private:
        ASvarDef *varDefList[MAX];
        ASstatement *statementList[MAX];
        int numVarDefs;
        int numStatements;
    };

}
#endif