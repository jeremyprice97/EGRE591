#include <iostream>
#include "ASdefinition.h"
#include "ASfuncdef.h"
#include "ASvarDef.h"
#include "JVMgenerateDefinition.h"

#include "JVMtargetCode.h"

#include "JVMgenerateStatement.h"
#include "JVMgenerateExpression.h"
#include "JVMgenUtils.h"
#include "JVMgenGlobals.h"

#include "codeLabel.h"

#include "GOTO.h"
#include "IFNE.h"
#include "INVOKESPECIAL.h"
#include "INVOKEVIRTUAL.h"
#include "LDC.h"

namespace toycalc {

  void JVMgenerateDefinition::genDefinition(ASdefinition *ast,JVMtargetCode *tc) {
	  //std::cout << "In gen read def\n";
    enum defType dtype = ast->getType();
	if(dtype==funcDef) {
		ASfuncDef *fd = dynamic_cast<ASfuncDef*>(ast);
		ASstatement *statement = fd->getStatement();
		JVMgenerateStatement::genStatement(statement, tc);
	} else if (dtype == varDef) {
		
	}
	
	
	
	
	
	
	
	
	
	/*enum stateType stype = ast->getType();
    if (stype==ASSIGNstate){
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
