#include <iostream>
#include "ASstatement.h"

namespace toycalc {

    enum stateType ASstatement::getType() {return type;}
    void ASstatement::setType(enum stateType t) {type = t;}
    std::string ASstatement::toTypeString(enum stateType t) {
        std::string s;
        switch(t) {
            case exprState:     s = "exprState"; break;
            case breakState:    s = "breakState"; break;
            case blockState:    s = "blockState"; break;
            case ifState:       s = "ifState"; break;
            case nullState:     s = "nullState"; break;
            case returnState:   s = "returnState"; break;
            case whileState:    s = "whileState"; break;
            case readState:     s = "readState"; break;
            case writeState:    s = "writeState"; break;
            case newLineState:  s = "newLineState"; break;
            default:            s = "error"; break;
        }
        return s;
    }

}