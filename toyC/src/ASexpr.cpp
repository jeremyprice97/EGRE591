#include <iostream>
#include <string>
#include "ASexpr.h"

namespace toycalc {
    ASexpr::ASexpr(TCtoken* opr, ASexpression* oper1, ASexpression* oper2){
        oper = opr;  op1 = oper1; op2 = oper2; setType(expr);
    }

    std::string ASexpr::toString() {
		std::cout << "I'm in ASexpr!! before?!!!\n";
		//std::string s = oper->getLexeme();
		std::cout << "got oper lexeme" + oper->toString() + "."<< std::endl;
		//std::string s1 = op1->toString();
		std::cout << "got first op1" << op1->toString()<< std::endl;
		std::string s2 = op2->toString();
		std::cout << "got second op2" << std::endl;
        return ("expr("+oper->toString()+","+
                op1->toString()+","+
                op2->toString()+")");

    }

    ASexpression* ASexpr::getOp1() { return op1; }
    ASexpression* ASexpr::getOp2() { return op2; }
    TCtoken* ASexpr::getOper() { return oper; }

}
