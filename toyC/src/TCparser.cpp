#include <iostream>
#include <typeinfo>

#include "TClexer.h"
#include "TCparser.h"
#include "TCoutput.h"
#include "TCglobals.h"
#include "TCtokens.h"
#include "TCsymbol.h"
#include "TCsymTable.h"

//#include "AbstractSyntax.h"

/*
concrete grammar:

ToyCProgram -> {Definition} EOF
Definition -> Type identifier ( functionDefinition | ; )
Type -> int | char
functionDefinition -> functionHeader functionBody
functionHeader -> ( [formalParamList])
functionBody -> compoundStatement
formalParamList -> Type identifier { , Type identifier }
Statement -> expressionStatement
			 | breakStatement
			 | compoundStatement
			 | ifStatement
			 | NullStatement
			 | ReturnStatement
			 | WhileStatement
			 | ReadStatement
			 | WriteStatement
			 | NewLineStatement		 
ExpressionStatement → Expression ;
BreakStatement → break ;
CompoundStatement → { { Type identifier ; } { Statement } }
IfStatement → if ( Expression ) Statement [ else Statement ]
NullStatement → ;
ReturnStatement → return [ Expression ] ;
WhileStatement → while ( Expression ) Statement
ReadStatement → read ( identifier { , identifier } ) ;
WriteStatement → write ( ActualParameters ) ;
NewLineStatement → newline ;
Expression → RelopExpression { assignop RelopExpression }
RelopExpression → SimpleExpression { relop SimpleExpression }
SimpleExpression → Term { addop Term }
Term → Primary { mulop Primary }
Primary → identifier [ FunctionCall ]
		  | number
		  | stringConstant
		  | charConstant
		  | ( Expression )
		  | ( − | not ) Primary
FunctionCall → ( [ ActualParameters ] )
ActualParameters → Expression { , Expression }			 

Abstract Syntax
Program -> prog(Definition*)
Definition -> funcDef(Id, Type, varDef(Id+, Type)*, Statement) | varDef(Id+, Type)
Statement -> exprState(Expression)
			| breakState()
			| blockState(varDef(Id+, Type)*, Statement*)
			| ifState(Expression, Statement, Statement?)
			| nullState()
			| returnState(Expression?)
			| whileState(Expression, Statement)
			| readState(Id+)
			| writeState(Expression+)
			| newLineState()
Expression -> Number | Identifier | CharLiteral | StringLiteral
			  | funcCall(Identifier, Expression*)
			  | expr(Operator, Expression, Expression)
			  | minus(Expression)
			  | not(Expression)
Operator -> + | − | ∗ | / | % | || | && | <= | < | = | > | >= | ! =
		 

*/

//todo: uncomment semantic actions
//todo: check "Subroutine parameters and/or return types must agree in number and type"
//todo: check "All expressions must be type compatible."
//todo: check "Division by zero is undefined."

namespace toycalc{
	
	//static void checkIfAllLabelTargetsAreDefined(ASprogram*);
	//static bool targetLabelExists(std::string,ASprogram*);
	static void enter_special_id(TCsymTable*,tokens);
	TCparser::TCparser(TClexer* s) { scanner = s; }
	
	ASabstractSyntax* TCparser::parse() {
		buff = scanner->getToken();
		ASabstractSyntax* p = toyCProgram();
		//checkIfAllLabelTargetsAreDefined((ASprogram*)p);
		return p;
	}
	
	void enteringDEBUG(std::string s) {
		if (verbose) reportDEBUG("    ","parser","entering "+s);
	}

	void exitingDEBUG(std::string s) {
		if (verbose) reportDEBUG("    ","parser","exiting "+s);
	}
	
	ASabstractSyntax* TCparser::toyCProgram(){
		int num = 0;
	    //toyCProgram -> {Definition} EOF
        enteringDEBUG("toyCProgram");
		ASdefinition *defList[MAX_DEFINITIONS];
		symTable = new TCsymTable();
        while(buff->getTokenType() != EOFILE){
            defList[num] = definition();
			num++;
        }
        exitingDEBUG("toyCProgram");
	    return new ASprogram(inputFileName, defList, num);
	}
	
	ASdefinition* TCparser::definition(){
		ASdefinition* d = NULL;
		int loc; TCsymbol *sym; 
        enteringDEBUG("definition");
        TCtoken* t = type();
        if(buff->getTokenType() == ID) {
			sym = symTable->getSym(buff);
			loc = symTable->find(buff->getLexeme());
			if(loc == -1) {
				loc = symTable->add(new TCsymbol(buff->getLexeme(), NO_TYPE));
				sym->setOffset(TCsymbol::getNextOffset());
			}
			enum symType stype = symTable->getSym(loc)->getType();
            buff = scanner->getToken();
            if (buff->getTokenType() != SEMICOLON) {
				if(stype == NO_TYPE) {
					symTable->getSym(loc)->setType(FUNC);
				} else if (stype == VAR) {
					reportSEMANTIC_ERROR(scanner, "function name expected");
					exit(EXIT_FAILURE);
				}
				
                d = functionDefinition(loc, t);
            } else {
				if(stype == NO_TYPE) {
					symTable->getSym(loc)->setType(VAR);
					sym->setOffset(TCsymbol::getNextOffset());
				}	
				else if (stype == FUNC) {
					reportSEMANTIC_ERROR(scanner, "variable name expected");
					exit(EXIT_FAILURE);
				}
                accept(SEMICOLON);
				d = new ASvarDef(loc, t);
            }
        } else {
            reportSYNTAX_ERROR(scanner, "identifier expected");
            exit(EXIT_FAILURE);
        }
        exitingDEBUG("definition");
        return d;
	}
	
	TCtoken* TCparser::type(){
		TCtoken* t = NULL;
        enteringDEBUG("type");
        if((buff->getTokenType() == INT) || (buff->getTokenType() == CHAR)){
			t = buff;
            buff = scanner->getToken();
        } else {
            reportSYNTAX_ERROR(scanner, "type expected");
            exit(EXIT_FAILURE);
        }
        exitingDEBUG("type");
        return t;
	}
	
	ASdefinition* TCparser::functionDefinition(int loc, TCtoken* type){
		ASdefinition* argList[MAX_ARGS]; ASstatement* s = NULL; int n;
		ASdefinition* f = NULL;
	    enteringDEBUG("functionDefinition");
	    n = functionHeader(argList);
	    s = functionBody();
	   
	    
		f = new ASfuncDef(loc, type, argList, s, n);
        exitingDEBUG("functionDefinition");
        return f;
	}
	
	int TCparser::functionHeader(ASdefinition* argList[]){
        int num = 0;
		enteringDEBUG("functionHeader");
        accept(LPAREN);
        if (buff->getTokenType() != RPAREN) {
            num = formalParamList(argList);
            accept(RPAREN);
        } else {
            accept(RPAREN);
        }
        exitingDEBUG("functionHeader");
        return num;
	}
	
	ASstatement* TCparser::functionBody(){
		ASstatement* s = NULL;
        enteringDEBUG("functionBody");
        s = compoundStatement();
        exitingDEBUG("functionBody");
        return s;
	}
	
	int TCparser::formalParamList(ASdefinition* argList[]){
		int loc; TCsymbol *sym; int num = 1;
	    enteringDEBUG("formalParamList");
	    TCtoken* t = type();
        if(buff->getTokenType() == ID) {
			sym = symTable->getSym(buff);
			loc = symTable->find(buff->getLexeme());
			if(loc == -1) {
				loc = symTable->add(new TCsymbol(buff->getLexeme(), NO_TYPE));
				sym->setOffset(TCsymbol::getNextOffset());
			}
			enum symType stype = symTable->getSym(loc)->getType();
			if(stype == NO_TYPE) {
				symTable->getSym(loc)->setType(VAR);
				sym->setOffset(TCsymbol::getNextOffset());
			} else if (stype == FUNC) {
				reportSEMANTIC_ERROR(scanner, "Redefinition of function name "+buff->getLexeme());
				exit(EXIT_FAILURE);
			}
            buff = scanner->getToken();
        } else {
            reportSYNTAX_ERROR(scanner, "identifier expected");
            exit(EXIT_FAILURE);
        }
		argList[0] = new ASvarDef(loc, t);
        while (buff->getTokenType() == COMMA){
			buff = scanner->getToken();
            t = type();
            if(buff->getTokenType() == ID) {
				sym = symTable->getSym(buff);
				loc = symTable->find(buff->getLexeme());
				if(loc == -1) {
					loc = symTable->add(new TCsymbol(buff->getLexeme(), NO_TYPE));
					sym->setOffset(TCsymbol::getNextOffset());
				}
				enum symType stype = symTable->getSym(loc)->getType();
				if(stype == NO_TYPE) {
					symTable->getSym(loc)->setType(VAR);
					sym->setOffset(TCsymbol::getNextOffset());
				} else if (stype == FUNC) {
					reportSEMANTIC_ERROR(scanner, "Redefinition of function name "+buff->getLexeme());
					exit(EXIT_FAILURE);
				}
				buff = scanner->getToken();
            } else {
                reportSYNTAX_ERROR(scanner, "identifier expected");
                exit(EXIT_FAILURE);
            }
			argList[num] = new ASvarDef(loc, t);
			num++;
        }
        exitingDEBUG("formalParamList");
        return num;
	}
	
	ASstatement* TCparser::statement(){
		ASstatement* s = NULL;
        enteringDEBUG("statement");
        if(buff->getTokenType() == ID || buff->getTokenType() == NUMBER || buff->getTokenType() == STRING || buff->getTokenType() == CHARLITERAL || buff->getTokenType() == LPAREN || buff->getTokenType() == ADDOP || buff->getTokenType() == NOT){
            s = expressionStatement();
        }
        else if(buff->getTokenType() == BREAK) {
            s = breakStatement();
        }
        else if(buff->getTokenType() == LCURLY) {
            s = compoundStatement();
        }
        else if(buff->getTokenType() == IF) {
            s = ifStatement();
        }
        else if(buff->getTokenType() == SEMICOLON) {
            s = nullStatement();
        }
        else if(buff->getTokenType() == RETURN) {
            s = returnStatement();
        }
        else if(buff->getTokenType() == WHILE) {
            s = whileStatement();
        }
        else if(buff->getTokenType() == READ) {
            s = readStatement();
        }
        else if(buff->getTokenType() == WRITE) {
            s = writeStatement();
        }
        else if(buff->getTokenType() == NEWLINE) {
            s = newlineStatement();
        }
        else {
            reportSYNTAX_ERROR(scanner, "statement expected");
            exit(EXIT_FAILURE);
        }
        exitingDEBUG("statement");
        return s;
	}
	
	ASstatement* TCparser::expressionStatement(){
		ASstatement* s = NULL;
        enteringDEBUG("expressionStatement");
        s = new ASexprState(expression());
        accept(SEMICOLON);
        exitingDEBUG("expressionStatement");
        return s;
	}
	
	ASstatement* TCparser::breakStatement(){
        enteringDEBUG("breakStatement");
        accept(BREAK);
        accept(SEMICOLON);
        exitingDEBUG("breakStatement");
        return new ASbreakState();
	}
	
	ASstatement* TCparser::compoundStatement(){
		ASstatement* cs = NULL;
		ASdefinition* lVarDefs[L_VAR_MAX];
		ASstatement* stateList[MAX_STATES];
		int numVars = 0;
		int numStates = 0;
		int loc;
		TCsymbol *sym = NULL; 
		TCtoken* t = NULL;
        enteringDEBUG("compoundStatement");
        accept(LCURLY);
        while((buff->getTokenType() == INT) || (buff->getTokenType() == CHAR)){
            t = type();
            if(buff->getTokenType() == ID) {
				sym = symTable->getSym(buff);
				loc = symTable->find(buff->getLexeme());
				if(loc == -1) {
					loc = symTable->add(new TCsymbol(buff->getLexeme(), NO_TYPE));
					sym->setOffset(TCsymbol::getNextOffset());
				}
				enum symType stype = symTable->getSym(loc)->getType();
				if(stype == NO_TYPE) {
					symTable->getSym(loc)->setType(VAR);
					sym->setOffset(TCsymbol::getNextOffset());
				} else if (stype == FUNC) {
					reportSEMANTIC_ERROR(scanner, "Redefinition of function name "+buff->getLexeme());
					exit(EXIT_FAILURE);
				}
				buff = scanner->getToken();
                accept(SEMICOLON);
            }
			lVarDefs[numVars] = new ASvarDef(loc, t);
			numVars++;
        }
        while(buff->getTokenType() != RCURLY) {
            stateList[numStates] = statement();
			++numStates;
        }
        accept(RCURLY);
		cs = new ASblockState(lVarDefs, stateList, numVars, numStates);
        exitingDEBUG("compoundStatement");
        return cs;
	}
	
	ASstatement* TCparser::ifStatement(){
		ASexpression* cond = NULL;
		ASstatement* s = NULL;
		ASstatement* e = NULL;
        enteringDEBUG("ifStatement");
        if(buff->getTokenType() == IF){
            buff = scanner->getToken();
        } else {
            reportSYNTAX_ERROR(scanner, "if expected");
            exit(EXIT_FAILURE);
        }
        accept(LPAREN);
        cond = expression();
        accept(RPAREN);
        s = statement();
        if(buff->getTokenType() == ELSE){
            buff = scanner->getToken();
            e = statement();
        }
        exitingDEBUG("ifStatement");
        return new ASifState(cond, s, e);
	}
	
	ASstatement* TCparser::nullStatement(){
        enteringDEBUG("nullStatement");
        accept(SEMICOLON);
        exitingDEBUG("nullStatement");
        return new ASnullState();
	}
	
	ASstatement* TCparser::returnStatement(){
		ASexpression* e = NULL;
        enteringDEBUG("returnStatement");
        accept(RETURN);
        if(buff->getTokenType() != SEMICOLON) {
            e = expression();
            accept(SEMICOLON);
        }
        else {
            accept(SEMICOLON);
        }
        exitingDEBUG("returnStatement");
        return new ASreturnState(e);
	}
	
	ASstatement* TCparser::whileStatement(){
		ASstatement* s = NULL;
		ASexpression* e = NULL;
        enteringDEBUG("whileStatement");
        accept(WHILE);
        accept(LPAREN);
        e = expression();
        accept(RPAREN);
        s = statement();
        exitingDEBUG("whileStatement");
        return new ASwhileState(e, s);
	}
	
	ASstatement* TCparser::readStatement(){
		int numID = 0;
		int loc;
		int idList[MAX_ID];
		is_input = 1;
		TCsymbol *sym;
        enteringDEBUG("readStatement");
		enter_special_id(symTable,READ);
        accept(READ);
        accept(LPAREN);
        if(buff->getTokenType() == ID) {
			sym = symTable->getSym(buff);
			loc = symTable->find(buff->getLexeme());
			if ( (sym->getType() == NO_TYPE) || (loc == -1)) {
				reportSEMANTIC_ERROR(scanner,"uninitialized variable");
				exit(EXIT_FAILURE);
			}
			if ( sym->getType() == FUNC ) {
				reportSEMANTIC_ERROR(scanner,"'"+sym->getId()+"' is a function");
				exit(EXIT_FAILURE);
			}
			idList[numID] = loc;
			++numID;
			buff = scanner->getToken();
		}
		
        while (buff->getTokenType() == COMMA) {
            accept(COMMA);
            if(buff->getTokenType() == ID) {
					sym = symTable->getSym(buff);
			loc = symTable->find(buff->getLexeme());
			if ( (sym->getType() == NO_TYPE) || (loc == -1)) {
				reportSEMANTIC_ERROR(scanner,"uninitialized variable");
				exit(EXIT_FAILURE);
			}
				idList[numID] = loc;
				++numID;
				buff = scanner->getToken();
			}
        }
        accept(RPAREN);
        accept(SEMICOLON);
        exitingDEBUG("readStatement");
        return new ASreadState(idList, numID);
	}
	
	ASstatement* TCparser::writeStatement(){
		is_output = 1; 
		ASexpression* expressionList[MAX_EXPRESSION];
        enteringDEBUG("writeStatement");
		enter_special_id(symTable,WRITE);
        accept(WRITE);
        accept(LPAREN);
        int num = actualParameters(expressionList);
        accept(RPAREN);
        accept(SEMICOLON);
        exitingDEBUG("writeStatement");
        return new ASwriteState(expressionList, num);
	}
	
	ASstatement* TCparser::newlineStatement(){
        enteringDEBUG("newlineStatement");
        accept(NEWLINE);
        accept(SEMICOLON);
        exitingDEBUG("newlineStatement");
        return new ASnewLineState();
	}
	

	ASexpression* TCparser::expression(){
		ASexpression* e1 = NULL;
		ASexpression* e2 = NULL;
		TCtoken* t = NULL;
        enteringDEBUG("expression");
        e1 = relopExpression();
        while(buff->getTokenType() == ASSIGNOP){
			t = buff;
            buff = scanner->getToken();
			e2 = relopExpression();
			e1 = new ASexpr(t, e1, e2);
        }
        exitingDEBUG("expression");
        return e1;
	}
	
	ASexpression* TCparser::relopExpression(){
		ASexpression* e1 = NULL;
		ASexpression* e2 = NULL;
		TCtoken* t = NULL;
        enteringDEBUG("relopExpression");
        e1 = simpleExpression();
        while(buff->getTokenType() == RELOP){
			t = buff;
            buff = scanner->getToken();
			e2 = simpleExpression();
            e1 = new ASexpr(t, e1, e2);
        }
        
        exitingDEBUG("relopExpression");
        return e1;
	}
	
	ASexpression* TCparser::simpleExpression(){
		ASexpression* e1 = NULL;
		ASexpression* e2 = NULL;
		TCtoken* t = NULL;
        enteringDEBUG("simpleExpression");
        e1 = term();
        while(buff->getTokenType() == ADDOP){
			t = buff;
            buff = scanner->getToken();
			e2 = term();
            e1 = new ASexpr(t, e1, e2);
        }
       
        exitingDEBUG("simpleExpression");
        return e1;
	}
	
	ASexpression* TCparser::term(){
		ASexpression* e1 = NULL;
		ASexpression* e2 = NULL;
		TCtoken* t = NULL;
        enteringDEBUG("term");
        e1 = primary();
        while(buff->getTokenType() == MULOP){
			t = buff;
            buff = scanner->getToken();
			e2 = primary();
			
			if (e2->getType() == simpleExpr) {
				ASsimpleExpr* s_e2 = (ASsimpleExpr*)e2;
				if (s_e2->getExpr()->getTokenType() == NUMBER) {
					if(s_e2->getExpr()->getLexeme() == "0") {
						reportSEMANTIC_ERROR(scanner, "divide by 0 undefined");
						exit(EXIT_FAILURE);
					}
				}
			}
            e1 = new ASexpr(t, e1, e2);
        }
        exitingDEBUG("term");
        return e1;
	}
	
	ASexpression* TCparser::primary(){
		int loc;
		int num = 0;
		TCtoken* t = NULL;
		TCtoken* t1 = NULL;
		TCsymbol* sym = NULL;
		ASexpression* e = NULL;
		ASexpression* expressionList[MAX_EXPRESSION];
        enteringDEBUG("primary");
        if(buff->getTokenType() == ID) {
			sym = symTable->getSym(buff);
			loc = symTable->find(buff->getLexeme());
			if ( (sym->getType() == NO_TYPE) || (loc == -1)) {
				reportSEMANTIC_ERROR(scanner,"uninitialized variable or function");
				exit(EXIT_FAILURE);
			}
			t = buff;
			
            buff = scanner->getToken();
            if(buff->getTokenType() != LPAREN) {
				e = new ASsimpleExpr(t);
				exitingDEBUG("primary");
				return e;
            }
				num = functionCall(expressionList);
                e = new ASfuncCall(loc,expressionList, num);
			
        }
        else if(buff->getTokenType() == NUMBER) {
			t = buff;
			e = new ASsimpleExpr(t);
            buff = scanner->getToken();
        }
        else if(buff->getTokenType() == STRING) {
			t = buff;
			e = new ASsimpleExpr(t);
            buff = scanner->getToken();
        }
        else if(buff->getTokenType() == CHARLITERAL) {
			t = buff;
			e = new ASsimpleExpr(t);
            buff = scanner->getToken();
        }
        else if(buff->getTokenType() == LPAREN) {
            accept(LPAREN);
            e = expression();
            accept(RPAREN);
        }
        else if(buff->getTokenType() == ADDOP) {
			t = buff;
			buff = scanner->getToken();
            e = new ASminus(primary());
		}			
		else if (buff->getTokenType() == NOT) {
			t = buff;
            buff = scanner->getToken();
            e = new ASnot(primary());
        }
        else {
            reportSYNTAX_ERROR(scanner, "primary expected");
            exit(EXIT_FAILURE);
        }
        exitingDEBUG("primary");
        return e;
	}
	
	int TCparser::functionCall(ASexpression* expressionStatement[]){
		int num = 0;
	    enteringDEBUG("functionCall");
        accept(LPAREN);
        if(buff->getTokenType() != RPAREN) {
            num = actualParameters(expressionStatement);
            accept(RPAREN);
        }
        else {
            accept(RPAREN);
        }
//std::cout << "parser: " << num << "\n";
        exitingDEBUG("functionCall");	
        return num;
	}
	
	int TCparser::actualParameters(ASexpression* expressionStatement[]){
		int num = 0;
        enteringDEBUG("actualParameters");
	    expressionStatement[num] = expression();
		++num;
	    while(buff->getTokenType() == COMMA){
			//std::cout << "why is this being called\n";
	        accept(COMMA);
	        expressionStatement[num] = expression();
			++num;
	    }
        exitingDEBUG("actualParameters");
        return num;
	}
	
	void TCparser::accept(int t) {
		if (t == buff->getTokenType())
			buff = scanner->getToken();
		else {
			std::string str="";
			str += t;
			reportSYNTAX_ERROR(scanner,str+" expected");
			exit(EXIT_FAILURE);
		}
	}
	static void enter_special_id(TCsymTable *st,tokens type) {
    TCsymbol *sym = new TCsymbol();
    sym->setType(VAR);
    sym->setId((type==READ)?"System.in":"System.out");
    sym->setOffset(TCsymbol::getNextOffset());
    st->add(sym);
  }
}