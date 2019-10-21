#include <iostream>

#include "ASvarDef.h"
#include "TCoutput.h"
#include "TCtokens.h"

namespace toycalc{

    ASvarDef::ASvarDef(int l, TCtoken* t) {
        ID = l; type = t;
    }

    int ASvarDef::getID() { return ID; }
    TCtoken* ASvarDef::getToken() { return type; }

    std::string ASvarDef::toString() {
        std::string s = "varDef(\n";
        s += ID + ",";
        s += type->toString() + ")\n";
        return s;
    }

}
