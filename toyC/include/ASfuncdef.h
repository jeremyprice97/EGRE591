#ifndef ASFUNCDEF_H
#define ASFUNCDEF_H

#include "ASabstractSyntax.h"
#include "ASstatement.h"
#include "TCtoken.h"
#include "ASvarDef.h"

#define MAX_STATEMENTS 500 // arbitrary

namespace toycalc {

    class ASfuncDef:public ASdefinition {
    public:
        ASfuncDef(int, TCtoken*, ASvarDef*[], ASstatement*, int);
        std::string toString();

        int getID();
        TCtoken *getToken();
        ASvarDef *getVarDefs(int);
        ASstatement *getStatement();
        int getNumVarDefs();

    private:
        int ID;
        TCtoken *type;
        ASvarDef *varDefsList[MAX_STATEMENTS];
        ASstatement *statement;
        int numVarDefs;
    };

}
#endif
