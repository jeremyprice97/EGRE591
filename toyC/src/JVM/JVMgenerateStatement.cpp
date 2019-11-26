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

#include "codeLabel.h"

#include "GOTO.h"
#include "IFNE.h"
#include "NOP.h"
#include "RETURN.h"
#include "INVOKESPECIAL.h"
#include "INVOKEVIRTUAL.h"
#include "LDC.h"

//todo: finish rest of statements
// filled in all but breakState

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
    } else if (stype == ifState) {                      //edited ifState 11/25
        ASifState *if_s = dynamic_cast<ASifState*>(ast);
        ASexpression *if_expr = dynamic_cast<ASexpression*>(if_s->getExpression());
        JVMgenerateExpression::genExpression(if_expr,tc);
        ASstatement *if_state1 = dynamic_cast<ASstatement*>(if_s->getStatement1());
        JVMgenerateStatement::genStatement(if_state1,tc);
        if(if_s->getStatement2() != NULL) {
            ASstatement *if_state2 = dynamic_cast<ASstatement *>(if_s->getStatement2());
            JVMgenerateStatement::genStatement(if_state2,tc);
        }
    } else if (stype == nullState) {                      //edited ifState 11/25
        ASnullState *ns = dynamic_cast<ASnullState*>(ast);
        tc->add(new NOP());
    } else if (stype == returnState) {                      //edited ifState 11/25
	    ASreturnState *rs = dynamic_cast<ASreturnState*>(ast);
	    if(rs->getExpression() != NULL){
            ASexpression *r_expr = dynamic_cast<ASexpression*>(rs->getExpression());
            JVMgenerateExpression::genExpression(r_expr,tc);
	    }
	    tc->add(new RETURN());
    } else if (stype == whileState) {                      //edited ifState 11/25
        ASwhileState *ws = dynamic_cast<ASwhileState*>(ast);
        ASexpression *w_expr = dynamic_cast<ASexpression*>(ws->getExpression());
        JVMgenerateExpression::genExpression(w_expr,tc);
        ASstatement *w_state = dynamic_cast<ASstatement*>(ws->getStatement());
        JVMgenerateStatement::genStatement(w_state,tc);
    } else if (stype == readState) {                      //edited ifState 11/25
        ASreadState *read_s = dynamic_cast<ASreadState*>(ast);
        int num = read_s->getNumIDs();
        for(int i=0; i < num; i++) {
            JVMgenerateExpression::genExpression(read_s->getID(i),tc);     //todo: must uncomment, only commented out to compile!!!!!
        }
        //do something else here?
    } else if (stype == writeState) {                      //edited ifState 11/25
        ASwriteState *write_s = dynamic_cast<ASwriteState*>(ast);
        int num = write_s->getNumExpressions();
        for(int i=0; i < num; i++) {
            JVMgenerateExpression::genExpression(write_s->getExpression(i),tc);
        }
        //do something else here?
    } else if (stype == newLineState) {                      //edited ifState 11/25
        //maybe NOP() here?
    }
	
	
	
	
	
	
	
	
	
	
	
	
    /*if (stype==ASSIGNstate){
      ASassignState *as = dynamic_cast<ASassignState*>(ast);
      ASexpr *expr = as->getExpression();
      JVMgenerateExpression::genExpression(expr,tc);
      JVMgenUtils::gen_ISTORE(*symTable->getSym(as->getVar()),tc);
    } else if (stype==WRITEstate) {
      ASwriteState *ws = dynamic_cast<ASwriteState*>(ast);
      ASsimpleExpr *sexpr = dynamic_cast<ASsimpleExpr*>(ws->getExpression());
      JVMgenUtils::gen_ALOAD(*symTable->getSym(symTable->find("System.out")),tc);
      JVMgenerateExpression::genExpression(sexpr,tc);
      tc->add(new INVOKEVIRTUAL(PRINT_INT_NEWLINE_METHOD_SPEC));
    } else if (stype==READstate) {
      ASreadState *rs = dynamic_cast<ASreadState*>(ast);
      // prompt first
      JVMgenUtils::gen_ALOAD(*symTable->getSym(symTable->find("System.out")),tc);
      tc->add(new LDC("input: "));
      tc->add(new INVOKEVIRTUAL(PRINT_STRING_METHOD_SPEC));
      // now input value
      JVMgenUtils::gen_ALOAD(*symTable->getSym(symTable->find("System.in")),tc);
      tc->add(new INVOKEVIRTUAL(READ_INT_METHOD_SPEC));
      JVMgenUtils::gen_ISTORE(*symTable->getSym(rs->getId()),tc);
    } else if (stype==IFstate) {
      ASifState *is = dynamic_cast<ASifState*>(ast);
      JVMgenerateExpression::genExpression(is->getExpression(),tc);
      tc->add(new IFNE(new label(symTable->getSym(is->getLabel())->getId())));
    } else if (stype==GOTOstate) {
      ASgotoState *gs = dynamic_cast<ASgotoState*>(ast);
      tc->add(new GOTO(new label(symTable->getSym(gs->getLabel())->getId())));
    } else if (stype==LABELstate) {
      ASlabelState *ls = dynamic_cast<ASlabelState*>(ast);
      tc->add(new codeLabel(symTable->getSym(ls->getLabel())->getId()));
      JVMgenerateStatement::genStatement(ls->getStatement(),tc);
    } else if (stype==SKIPstate) {
      // do nothing
    }*/
  }

}
