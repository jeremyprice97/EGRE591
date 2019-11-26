#include <iostream>
#include <string>

#include "JVMgenerateExpression.h"

#include "ASexpression.h"
#include "ASexpr.h"
//#include "ASbinaryExpr.h"
//#include "ASunaryExpr.h"
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

//todo: finish funcCall -> added some code, some questions about the logic and how to go about it
// minus -> added code
// NoT -> added code
//todo: maybe fix assignop

namespace toycalc {
  void JVMgenerateExpression::genExpression(ASexpression *ast,JVMtargetCode *tc) {
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
          }
      } else if (etype == funcCall) {                      //edited ifState 11/25
          ASfuncCall *call_s = dynamic_cast<ASfuncCall*>(ast);
          //ASsimpleExpr *simp_expr = dynamic_cast<ASsimpleExpr*>(call_s->getID());     //todo: is it this line and the next line?
          //JVMgenerateExpression::genExpression(simp_expr,tc);                       //
          genExpression(call_s->getID(),tc);      //todo: must uncomment, only commented out to compile!!!!!             // or just this one? or does it matter?
          int num = call_s->getNumExpressions();
          for(int i=0; i < num; i++) {
              //ASexpression *func_expr = dynamic_cast<ASexpression *>(call_s->getExpression());
              genExpression(call_s->getExpression(i), tc);
              //JVMgenerateExpression::genExpression(func_expr(i), tc);
          }
      } else if (etype == expr) {
          ASexpr *e = dynamic_cast<ASexpr *>(ast);
          genExpression(e->getOp1(), tc);
          genExpression(e->getOp2(), tc);
          TCtoken *op = e->getOper();
          switch (op->getTokenType()) {
              case ADDOP:
                  JVMgenUtils::gen_ADDOP(*op, tc);
                  break;
              case MULOP:
                  JVMgenUtils::gen_MULOP(*op, tc);
                  break;
              case RELOP:
                  JVMgenUtils::gen_RELOP(*op, tc);
                  break;
                  //case OR:    JVMgenUtils::gen_OR(*op,tc); break; //not needed, already taken care of in ADDOP
                  //case AND:   JVMgenUtils::gen_AND(*op,tc); break;//not needed, already taken care of in MULOP
              case ASSIGNOP: {
                  ASsimpleExpr *exp1 = dynamic_cast<ASsimpleExpr *>(e->getOp1());
                  TCtoken *tok1 = exp1->getExpr();
                  JVMgenUtils::gen_ISTORE(*symTable->getSym(tok1), tc);
                  } break;
              default: // shouldn't happen
                  std::cerr << "Fatal internal error #1: JVMgenerateExpression" << std::endl;
                  exit(EXIT_FAILURE);
          }
      } else if (etype == minus) {                      //edited ifState 11/25
          ASminus *minus_s = dynamic_cast<ASminus*>(ast);
          ASexpression *min_expr = dynamic_cast<ASexpression*>(minus_s->getExpression());
          JVMgenerateExpression::genExpression(min_expr,tc);
      } else if (etype == NoT) {                      //edited ifState 11/25
          ASnot *not_s = dynamic_cast<ASnot*>(ast);
          ASexpression *not_expr = dynamic_cast<ASexpression*>(not_s->getExpression());
          JVMgenerateExpression::genExpression(not_expr,tc);
      }
      /* if (etype==BINARYexpr){
         ASbinaryExpr *be = dynamic_cast<ASbinaryExpr*>(ast);
         genExpression(be->getOp1(),tc); genExpression(be->getOp2(),tc);
         TCtoken *op = be->getOper();
         switch (op->getTokenType()) {
         case ADDOP: JVMgenUtils::gen_ADDOP(*op,tc); break;
         case MULOP: JVMgenUtils::gen_MULOP(*op,tc); break;
         case RELOP: JVMgenUtils::gen_RELOP(*op,tc); break;
         case OR:    JVMgenUtils::gen_OR(*op,tc); break;
         case AND:   JVMgenUtils::gen_AND(*op,tc); break;
         default: // shouldn't happen
           std::cerr << "Fatal internal error #1: JVMgenerateExpression" << std::endl;
           exit(EXIT_FAILURE);
         }
       } else if (etype==UNARYexpr) {
         ASunaryExpr *ue = dynamic_cast<ASunaryExpr*>(ast);
         genExpression(ue->getExpr(),tc);
         tc->add(new INEG());
       } else if (etype==SIMPLEexpr) {
          ASsimpleExpr *se = dynamic_cast<ASsimpleExpr*>(ast);
         TCtoken *t = se->getExpr();
         std::string lexeme = t->getLexeme();
         if(t->getTokenType()==ID) {
           TCsymbol *idsym = symTable->getSym(symTable->find(lexeme));
           JVMgenUtils::gen_ILOAD(*idsym,tc);
         } else if(t->getTokenType()==NUM) {
          JVMgenUtils::gen_ICONST(stoi(lexeme),tc);
         } else { // shouldn't happen
           std::cerr << "Fatal internal error #2: JVMgenerateExpression" << std::endl;
           exit(EXIT_FAILURE);
         }
       }*/
  }
}
