#include <iostream>
#include "ASdefinition.h"

namespace toycalc {

    enum defType ASdefinition::getType() {return type;}
    void ASdefinition::setType(enum defType t) {type = t;}
//    std::string ASdefinition::toTypeString(enum defType t) {
//        std::string s;
//        switch(t) {
//            case funcDef:     s = "exprState"; break;
//            case varDef:      s = "breakState"; break;
//            default:          s = "error"; break;
//        }
//        return s;
//    }

}