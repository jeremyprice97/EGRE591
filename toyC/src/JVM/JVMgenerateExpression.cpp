#include <iostream>
#include <string>

#include "JVMgenerateExpression.h"

#include "ASexpression.h"
#include "ASexpr.h"
#include "ASsimpleExpr.h"
#include "ASfuncCall.h"
#include "ASminus.h"
#include "ASnot.h"
#include "JVMtargetCode.h"
#include "JVMgenUtils.h"
#include "TCtoken.h"
#include "TCtokens.h"
#include "TCglobals.h"

#include "INEG.h"
#include "LDC.h"

//todo: finish funcCall -> added some code, some questions about the logic and how to go about it

namespace toycalc {
  int JVMgenerateExpression::genExpression(ASexpression *ast,JVMtargetCode *tc) {
      enum exprType etype = ast->getType();
      if (etype == simpleExpr) {
          ASsimpleExpr *se = dynamic_cast<ASsimpleExpr *>(ast);
          TCtoken *t = se->getExpr();
          std::string lexeme = t->getLexeme();
          if (t->getTokenType() == ID) {
              TCsymbol *idsym = symTable->getSym(symTable->find(lexeme));
              JVMgenUtils::gen_ILOAD(*idsym, tc);
          } else if (t->getTokenType() == NUMBER) {
              JVMgenUtils::gen_ICONST(stoi(lexeme), tc);
			 
          } else if (t->getTokenType() == STRING) {
			  tc->add(new LDC(t->getLexeme()));
		  }
		  return t->getTokenType();
      } else if (etype == funcCall) {
          /*ASfuncCall *call_s = dynamic_cast<ASfuncCall*>(ast);
          //ASsimpleExpr *simp_expr = dynamic_cast<ASsimpleExpr*>(call_s->getID());
          //JVMgenerateExpression::genExpression(simp_expr,tc);
          genExpression(call_s->getID(),tc);
          int num = call_s->getNumExpressions();
          for(int i=0; i < num; i++) {
              //ASexpression *func_expr = dynamic_cast<ASexpression *>(call_s->getExpression());
              genExpression(call_s->getExpression(i), tc);
              //JVMgenerateExpression::genExpression(func_expr(i), tc);
          }*/
      } else if (etype == expr) {
		  int t = 0;
          ASexpr *e = dynamic_cast<ASexpr *>(ast);
          TCtoken *op = e->getOper();
          switch (op->getTokenType()) {
              case ADDOP:
				  t = genExpression(e->getOp1(), tc);
				  genExpression(e->getOp2(), tc);
                  JVMgenUtils::gen_ADDOP(*op, tc);
                  break;
              case MULOP:
				  t = genExpression(e->getOp1(), tc);
				  genExpression(e->getOp2(), tc);
                  JVMgenUtils::gen_MULOP(*op, tc);
                  break;
              case RELOP:
				  t = genExpression(e->getOp1(), tc);
				  genExpression(e->getOp2(), tc);
                  JVMgenUtils::gen_RELOP(*op, tc);
                  break;
              case ASSIGNOP: {
				  t = 1;
				  genExpression(e->getOp2(), tc);
				  ASexpression *op2_e = dynamic_cast<ASexpression*>(e->getOp2());
				  if ((op2_e->getType() != simpleExpr)) {
					ASexpr *op2_e_expr = dynamic_cast<ASexpr *>(e->getOp2());  
					genExpression(op2_e_expr->getOp1(), tc);
				  }
				  else {
					//std::cout << "CODE GEN - ERROR, assign target not a variable" << std::endl;
				  }
				  ASexpression *op1_e = dynamic_cast<ASexpression*>(e->getOp1());	  
				  
				  if (op1_e->getType() == simpleExpr) {
					ASsimpleExpr *exp1 = dynamic_cast<ASsimpleExpr *>(e->getOp1());
					TCtoken *tok1 = exp1->getExpr();
					JVMgenUtils::gen_ISTORE(*symTable->getSym(tok1), tc);
				  }
				  else {
					  
					genExpression(e->getOp1(), tc);
					
				  } 
                  } break;
              default: // shouldn't happen
                  std::cerr << "Fatal internal error #1: JVMgenerateExpression" << std::endl;
                  exit(EXIT_FAILURE);
          }
		  return t;
      } else if (etype == minus){
          ASminus *minus_s = dynamic_cast<ASminus*>(ast);
          ASexpression *min_expr = dynamic_cast<ASexpression*>(minus_s->getExpression());
          int t = genExpression(min_expr,tc);
          tc->add(new INEG());
		  return t;
      } else if (etype == NoT) {
          ASnot *not_s = dynamic_cast<ASnot*>(ast);
          ASexpression *not_expr = dynamic_cast<ASexpression*>(not_s->getExpression());
         int t =  JVMgenerateExpression::genExpression(not_expr,tc);
          JVMgenUtils::gen_NOT(tc);
		  return t;
      }
  }
}
