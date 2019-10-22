#ifndef ASBLOCKSTATE_H
#define ASBLOCKSTATE_H

//#include "ASabstractSyntax.h"
#include "ASstatement.h"
#include "ASvarDef.h"

#define MAX 500

namespace toycalc {

    class ASblockState:public ASstatement {
    public:
        ASblockState(ASdefinition*[],ASstatement*[],int,int);
        std::string toString();

        ASdefinition *getVarDefs(int);
        ASstatement *getStatements(int);
        int getNumVarDefs();
        int getNumStatements();

    private:
        ASdefinition *varDefList[MAX];
        ASstatement *statementList[MAX];
        int numVarDefs;
        int numStatements;
    };

}
#endif