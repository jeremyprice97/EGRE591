#include <iostream>

#include "ASvarDef.h"
#include "TCoutput.h"
#include "TCtokens.h"
#include "TCglobals.h"
namespace toycalc{

    ASvarDef::ASvarDef(int l, TCtoken* t) {
        ID = l; type = t;
        setType(varDef);
    }

    int ASvarDef::getID() { return ID; }
    TCtoken* ASvarDef::getToken() { return type; }

    std::string ASvarDef::toString() {
        std::string s = "varDef(";
        s += symTable->getSym(ID)->toString() + ",";
        s += type->toString() + ")";
        return s;
    }

}
