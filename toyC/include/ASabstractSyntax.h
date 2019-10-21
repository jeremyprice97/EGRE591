#ifndef ASABSTRACTSYNTAX_H
#define ASABSTRACTSYNTAX_H

#include <string>

namespace toycalc {
  
class ASabstractSyntax{
    public:
        virtual std::string toString() = 0;
    };

}
#endif
