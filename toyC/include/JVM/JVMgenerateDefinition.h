#ifndef JVMGENERATEDEFINITION_H
#define JVMGENERATEDEFINITION_H


#include "TCglobals.h"
#include "TCsymTable.h"

#include "ASdefinition.h"
#include "ASstatement.h"
#include "JVMtargetCode.h"

/*
// D. Resler 4/2010
*/
namespace toycalc {

    class JVMgenerateDefinition {
    public:
        static void genDefinition(ASdefinition*,JVMtargetCode*);

    };

}


#endif //COMPILERS_JVMGENERATEDEFINITION_H
