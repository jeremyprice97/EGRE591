#ifndef ASVARDEF_H
#define ASVARDEF_H

#include "ASabstractSyntax.h"
#include "ASdefinition.h"
//#include "ASfuncDef.h"
#include "TCtoken.h"

#define MAX_STATEMENTS 500 // arbitrary

namespace toycalc {

    class ASvarDef:public ASdefinition {
    public:
        ASvarDef(int,TCtoken*);
        std::string toString();

        int getID();
        TCtoken *getToken();

    private:
        TCtoken *type;
        int ID;
    };

}
#endif
