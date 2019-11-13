#ifndef ASDEFINITION_H
#define ASDEFINITION_H

#include "ASabstractSyntax.h"
//#include "ASprogram.h"

namespace toycalc {

    enum defType {
        funcDef, varDef
    };

    class ASdefinition : public ASabstractSyntax {
    public:
        virtual std::string toString() = 0;

        enum defType getType();

        void setType(enum defType);
        //std::string toTypeString(enum defType);

    private:
        enum defType type;
    };

}

#endif
