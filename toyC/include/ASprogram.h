#ifndef ASPROGRAM_H
#define ASPROGRAM_H

#include "ASabstractSyntax.h"
#include "ASdefinition.h"
//#include "ASfuncDef.h"
//#include "ASvarDef.h"

#define MAX_STATEMENTS 500 // arbitrary

namespace toycalc {
  
    class ASprogram:public ASabstractSyntax {
    public:
        ASprogram(std::string, ASdefinition*[], int);
        std::string toString();

        std::string getName();
        ASdefinition *getDefinition(int);
        int getNumDefinitions();

    private:
        ASdefinition *definitionList[MAX_STATEMENTS];
        std::string name;
        int numDefinitions;
    };
 
}
#endif
