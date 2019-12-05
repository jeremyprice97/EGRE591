#include <iostream>
#include <string>

#include "JVMgenerateExpression.h"
#include "INVOKESTATIC.h"

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
          int nameLoc = call_s->getID();
          //TCtoken *to = simp_expr->getExpr();
          //std::string lex = to->getLexeme();
          //TCsymbol *callID = symTable->getSym(symTable->find(lex));
          //JVMgenUtils::gen_ILOAD(*callID, tc);
          int num = call_s->getNumExpressions();
          INVOKESTATIC *invs = new INVOKESTATIC(symTable->getSym(nameLoc)->getId(),"I");
          invs->addArgList(num);
          tc->add(invs);

          //JVMgenerateExpression::genExpression(simp_expr,tc);
          //genExpression(call_s->getID(),tc);
          //int num = call_s->getNumExpressions();
          for(int i=0; i < num; i++) {
              //ASexpression *func_expr = dynamic_cast<ASexpression *>(call_s->getExpression(i));
              //genExpression(call_s->getExpression(i), tc);
              JVMgenerateExpression::genExpression(call_s->getExpression(i), tc);
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
				  //std::cout << "relop begin" << std::endl;
				  t = genExpression(e->getOp1(), tc);
				  genExpression(e->getOp2(), tc);
                  JVMgenUtils::gen_RELOP(*op, tc);
				 // std::cout << "relop end: " << op->getLexeme() <<std::endl;
                  break;
              case ASSIGNOP: {
				  t = 1;
				  
				 				  
				  ASexpression *op2_e = dynamic_cast<ASexpression*>(e->getOp2());
				  ASexpression *op1_e = dynamic_cast<ASexpression*>(e->getOp1());
				  
				  if (op2_e->getType() == expr) {
					  genExpression(e->getOp2(), tc); 
					  ASexpr* op2_assign = dynamic_cast<ASexpr*>(op2_e);
					  if(op2_assign->getOper()->getTokenType() == ASSIGNOP) {
						  if(op2_assign->getOp1()->getType() == simpleExpr) {
							ASsimpleExpr *op2_sim = dynamic_cast<ASsimpleExpr *>(op2_assign->getOp1()); 
							TCtoken* tok2 = op2_sim->getExpr();
							JVMgenUtils::gen_ILOAD(*symTable->getSym(tok2), tc);
						  }
					  }
				  }
				  else  {
					genExpression(e->getOp2(), tc); 
				  }
				  if (op1_e->getType() == simpleExpr) {
					ASsimpleExpr *exp1 = dynamic_cast<ASsimpleExpr *>(e->getOp1());
					TCtoken *tok1 = exp1->getExpr();
					JVMgenUtils::gen_ISTORE(*symTable->getSym(tok1), tc);
				  }				  
                  } break;
              default: // shouldn't happen
                  std::cerr << "Fatal internal error #1: JVMgenerateExpression" << std::endl;
                  exit(EXIT_FAILURE);
          }
		  return t;
      } else if (etype == minus){
		 // std::cout << "minus begin" << std::endl;
          ASminus *minus_s = dynamic_cast<ASminus*>(ast);
          ASexpression *min_expr = dynamic_cast<ASexpression*>(minus_s->getExpression());
          int t = genExpression(min_expr,tc);
          tc->add(new INEG());
		 // std::cout << "minus end" << std::endl;
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
