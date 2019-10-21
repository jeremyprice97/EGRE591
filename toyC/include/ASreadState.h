#ifndef ASREADSTATE_H
#define ASREADSTATE_H

#include "ASstatement.h"

#define MAX 500 // arbitrary

namespace toycalc {

    class ASreadState:public ASstatement {
    public:
        ASreadState(int [],int);
        std::string toString();

        int getID(int);
        int getNumIDs();

    private:
        int ID[MAX];
        int numIDs;
    };

}
#endif
