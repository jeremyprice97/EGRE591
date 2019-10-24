#include <iostream>

#include "ASreadState.h"
#include "TCoutput.h"
#include "TCglobals.h"

namespace toycalc {

    ASreadState::ASreadState(int l[], int num) {
        for (int i=0; i < num; i++) ID[i] = l[i];
        numIDs = num;
        setType(readState);
    }

    int ASreadState::getID(int n) { return ID[n]; }
    int ASreadState::getNumIDs() { return numIDs; }

    std::string ASreadState::toString() {
        if (numIDs==0) return "readState([])";
        std::string s = "readState(\n";
        indent();
        s += spaces() + "[\n";
        indent();
        if (numIDs > 0) {
            s += spaces();
            s += symTable->getSym(ID[0])->toString();
            for (int i=1; i < numIDs; i++) {
                s += ",\n" + spaces();
                s += symTable->getSym(ID[i])->toString();
            }
        }
        outdent();
        s += "\n"+spaces() + "]\n";
        outdent();
        s += spaces() + ")";
        return s;
    }

}
