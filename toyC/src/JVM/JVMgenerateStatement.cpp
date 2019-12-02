#include <iostream>
#include "ASstatement.h"

#include "ASexprState.h"
#include "ASbreakState.h"
#include "ASblockState.h"
#include "ASifState.h"
#include "ASnullState.h"
#include "ASreturnState.h"
#include "ASwhileState.h"
#include "ASwriteState.h"
#include "ASreadState.h"
#include "ASnewLineState.h"

#include "JVMtargetCode.h"

#include "JVMgenerateStatement.h"
#include "JVMgenerateExpression.h"
#include "JVMgenUtils.h"
#include "JVMgenGlobals.h"

//#include "TCtoken.h"
//#include "TCtokens.h"
//#include "TCglobals.h"
#include "label.h"
#include "codeLabel.h"
#include "IF_ICMPEQ.h"
#include "POP.h"


#include "GOTO.h"
#include "IFNE.h"
#include "ICONST_0.h"
#include "ICONST_1.h"
#include "RETURN.h"
#include "INVOKESPECIAL.h"
#include "INVOKEVIRTUAL.h"
#include "LDC.h"
#include "IFNE.h"
#include "IFEQ.h"
#include "DUP.h"


namespace toycalc {

  void JVMgenerateStatement::genStatement(ASstatement *ast,JVMtargetCode *tc) {
    enum stateType stype = ast->getType();
	if (stype == exprState) {
        ASexprState *es = dynamic_cast<ASexprState*>(ast);
        ASexpression *expr = dynamic_cast<ASexpression*>(es->getExpression());
        JVMgenerateExpression::genExpression(expr,tc);
    } else if (stype == breakState) {

    } else if (stype == blockState) {
        ASblockState *bs = dynamic_cast<ASblockState*>(ast);
        int num = bs->getNumStatements();
        for(int i=0; i < num; i++) {
            JVMgenerateStatement::genStatement(bs->getStatement(i),tc);
        }
    } else if (stype == ifState) {
        ASifState *if_s = dynamic_cast<ASifState*>(ast);
        ASexpression *if_expr = dynamic_cast<ASexpression*>(if_s->getExpression());
        JVMgenerateExpression::genExpression(if_expr,tc);
        ASstatement *if_state1 = dynamic_cast<ASstatement*>(if_s->getStatement1());
		tc->add(new ICONST_0());
		label *l0 = new label(); label *l1 = new label();
		tc->add(new IF_ICMPEQ(l0));
        JVMgenerateStatement::genStatement(if_state1,tc);
		tc->add(new ICONST_1());
		tc->add(new GOTO(l1));
        tc->add(new codeLabel(l0->toString()+""));
		tc->add(new ICONST_0());
		tc->add(new codeLabel(l1->toString()+""));
		if(if_s->getStatement2() != NULL) {
			tc->add(new ICONST_1());
			label *l2 = new label();
			tc->add(new IF_ICMPEQ(l2));
            ASstatement *if_state2 = dynamic_cast<ASstatement *>(if_s->getStatement2());
            JVMgenerateStatement::genStatement(if_state2,tc);
			tc->add(new codeLabel(l2->toString()+""));
        }
		else tc->add(new POP());
    } else if (stype == nullState) {
        tc->add(new ICONST_0());
    } else if (stype == returnState) {
	    ASreturnState *rs = dynamic_cast<ASreturnState*>(ast);
	    if(rs->getExpression() != NULL){
            ASexpression *r_expr = dynamic_cast<ASexpression*>(rs->getExpression());
            JVMgenerateExpression::genExpression(r_expr,tc);
	    }
	    tc->add(new RETURN());
    } else if (stype == whileState) {
		label *l0 = new label(); label *l1 = new label();
        ASwhileState *ws = dynamic_cast<ASwhileState*>(ast);
        ASexpression *w_expr = dynamic_cast<ASexpression*>(ws->getExpression());
		ASstatement *w_state = dynamic_cast<ASstatement*>(ws->getStatement());	
		
		tc->add(new codeLabel(l0->toString()+""));
        JVMgenerateExpression::genExpression(w_expr,tc);
		tc->add(new ICONST_0());
		tc->add(new IF_ICMPEQ(l1));
		
		JVMgenerateStatement::genStatement(w_state,tc);
		tc->add(new GOTO(l0));
		tc->add(new codeLabel(l1->toString()+""));
		
    } else if (stype == readState) {
        ASreadState *read_s = dynamic_cast<ASreadState*>(ast);
        int num = read_s->getNumIDs();
        // now input value
		
        for(int i=0; i < num; i++) {
            JVMgenUtils::gen_ALOAD(*symTable->getSym(symTable->find("System.in")),tc);
            tc->add(new INVOKEVIRTUAL(READ_INT_METHOD_SPEC));
            JVMgenUtils::gen_ISTORE(*symTable->getSym(read_s->getID(i)), tc);
        }
    } else if (stype == writeState) {
        ASwriteState *write_s = dynamic_cast<ASwriteState*>(ast);
        int num = write_s->getNumExpressions();
        for(int i=0; i < num; i++) {
            JVMgenUtils::gen_ALOAD(*symTable->getSym(symTable->find("System.out")),tc);
			
            int t = JVMgenerateExpression::genExpression(write_s->getExpression(i),tc);
			if(t == 10) { //string enum type, clashes with JVM instruction return if included here
				tc->add(new INVOKEVIRTUAL(PRINT_STRING_METHOD_SPEC));
			}
			else {
				tc->add(new INVOKEVIRTUAL(PRINT_INT_NEWLINE_METHOD_SPEC));
			}
        }
    } else if (stype == newLineState) {
		JVMgenUtils::gen_ALOAD(*symTable->getSym(symTable->find("System.out")),tc);
        tc->add(new LDC("\"\\n\""));
		tc->add(new INVOKEVIRTUAL(PRINT_STRING_METHOD_SPEC));
    }
  }
}
