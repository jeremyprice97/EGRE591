#include <iostream>
#include "ASexpression.h"

namespace toycalc {

    enum exprType ASexpression::getType() {return type;}
    void ASexpression::setType(enum exprType t) {type = t;}
    std::string ASexpression::toTypeString(enum exprType t) {
		//std::cout << "I'm in ASexpression!! before?!!!\n";
        std::string s;
        switch(t) {
            case simpleExpr:     s = "simpleExpr"; break;
            case funcCall:    s = "funcCall"; break;
            case expr:    s = "expr"; break;
            case minus:       s = "minus"; break;
            case NoT:     s = "not"; break;
            default:            s = "error"; break;
        }
        return s;
    }

}