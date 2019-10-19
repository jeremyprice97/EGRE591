#include <iostream>
#include <typeinfo>

#include "TClexer.h"
#include "TCparser.h"
#include "TCoutput.h"
#include "TCglobals.h"
#include "TCtokens.h"
#include "TCsymbol.h"
#include "TCsymTable.h"

int num;

//return 0 valid, return -1 syntax error

namespace toycalc{
	
	TCparser::TCparser(TClexer* s) { scanner = s; }
	
	int TCparser::parse() {
		buff = scanner->getToken();
		//ASabstractSyntax* p = program();
		//checkIfAllLabelTargetsAreDefined((ASprogram*)p);
		return toyCProgram();
	}
	
	void enteringDEBUG(std::string s) {
		if (verbose) reportDEBUG("    ","parser","entering "+s);
	}

	void exitingDEBUG(std::string s) {
		if (verbose) reportDEBUG("    ","parser","exiting "+s);
	}
	
	int TCparser::toyCProgram(){
	    //toyCProgram -> {Definition} EOF
        enteringDEBUG("toyCProgram");
        while(buff->getTokenType() != EOFILE){
            num = definition();
        }
        exitingDEBUG("toyCProgram");
	    return 0;
	}
	
	int TCparser::definition(){
        enteringDEBUG("definition");
        num = type();
        if(buff->getTokenType() == ID) {
            buff = scanner->getToken();
            if (buff->getTokenType() != SEMICOLON) {
                num = functionDefinition();
            } else {
                accept(SEMICOLON);
            }
        } else {
            reportSYNTAX_ERROR(scanner, "identifier expected");
            exit(EXIT_FAILURE);
        }
        exitingDEBUG("definition");
        return 0;
	}
	
	int TCparser::type(){
        enteringDEBUG("type");
        if((buff->getTokenType() == INT) || (buff->getTokenType() == CHAR)){
            buff = scanner->getToken();
        } else {
            reportSYNTAX_ERROR(scanner, "type expected");
            exit(EXIT_FAILURE);
        }
        exitingDEBUG("type");
        return 0;
	}
	
	int TCparser::functionDefinition(){
	    enteringDEBUG("functionDefinition");
	    num = functionHeader();
	    num = functionBody();
        exitingDEBUG("functionDefinition");
        return 0;
	}
	
	int TCparser::functionHeader(){
        enteringDEBUG("functionHeader");
        accept(LPAREN);
        if (buff->getTokenType() != RPAREN) {
            num = formalParamList();
            accept(RPAREN);
        } else {
            accept(RPAREN);
        }
        exitingDEBUG("functionHeader");
        return 0;
	}
	
	int TCparser::functionBody(){
        enteringDEBUG("functionBody");
        num = compoundStatement();
        exitingDEBUG("functionBody");
        return 0;
	}
	
	int TCparser::formalParamList(){
	    enteringDEBUG("formalParamList");
	    num = type();
        if(buff->getTokenType() == ID) {
            buff = scanner->getToken();
        } else {
            reportSYNTAX_ERROR(scanner, "identifier expected");
            exit(EXIT_FAILURE);
        }
        while (buff->getTokenType() == COMMA){
            num = type();
            if(buff->getTokenType() == ID) {
                buff = scanner->getToken();
            } else {
                reportSYNTAX_ERROR(scanner, "identifier expected");
                exit(EXIT_FAILURE);
            }
        }
        exitingDEBUG("formalParamList");
        return 0;
	}
	
	int TCparser::statement(){
        enteringDEBUG("statement");
        if(buff->getTokenType() == ID || buff->getTokenType() == NUMBER || buff->getTokenType() == STRING || buff->getTokenType() == CHARLITERAL || buff->getTokenType() == LPAREN || buff->getTokenType() == ADDOP || buff->getTokenType() == NOT){
            num = expressionStatement();
        }
        else if(buff->getTokenType() == BREAK) {
            num = breakStatement();
        }
        else if(buff->getTokenType() == LCURLY) {
            num = compoundStatement();
        }
        else if(buff->getTokenType() == IF) {
            num = ifStatement();
        }
        else if(buff->getTokenType() == SEMICOLON) {
            num = nullStatement();
        }
        else if(buff->getTokenType() == RETURN) {
            num = returnStatement();
        }
        else if(buff->getTokenType() == WHILE) {
            num = whileStatement();
        }
        else if(buff->getTokenType() == READ) {
            num = readStatement();
        }
        else if(buff->getTokenType() == WRITE) {
            num = writeStatement();
        }
        else if(buff->getTokenType() == NEWLINE) {
            num = newlineStatement();
        }
        else {
            reportSYNTAX_ERROR(scanner, "statement expected");
            exit(EXIT_FAILURE);
        }
        exitingDEBUG("statement");
        return 0;
	}
	
	int TCparser::expressionStatement(){
        enteringDEBUG("expressionStatement");
        num = expression();
        accept(SEMICOLON);
        exitingDEBUG("expressionStatement");
        return 0;
	}
	
	int TCparser::breakStatement(){
        enteringDEBUG("breakStatement");
        accept(BREAK);
        accept(SEMICOLON);
        exitingDEBUG("breakStatement");
        return 0;
	}
	
	int TCparser::compoundStatement(){
        enteringDEBUG("compoundStatement");
        accept(LCURLY);
        while((buff->getTokenType() == INT) || (buff->getTokenType() == CHAR)){
            num = type();
            if(buff->getTokenType() == ID) {
                buff = scanner->getToken();
                accept(SEMICOLON);
            }
        }
        while(buff->getTokenType() != RCURLY) {
            num = statement();
        }
        accept(RCURLY);
        exitingDEBUG("compoundStatement");
        return 0;
	}
	
	int TCparser::ifStatement(){
        enteringDEBUG("ifStatement");
        if(buff->getTokenType() == IF){
            buff = scanner->getToken();
        } else {
            reportSYNTAX_ERROR(scanner, "if expected");
            exit(EXIT_FAILURE);
        }
        accept(LPAREN);
        num = expression();
        accept(RPAREN);
        num = statement();
        if(buff->getTokenType() == ELSE){
            buff = scanner->getToken();
            num = statement();
        }
        exitingDEBUG("ifStatement");
        return 0;
	}
	
	int TCparser::nullStatement(){
        enteringDEBUG("nullStatement");
        accept(SEMICOLON);
        exitingDEBUG("nullStatement");
        return 0;
	}
	
	int TCparser::returnStatement(){
        enteringDEBUG("returnStatement");
        accept(RETURN);
        if(buff->getTokenType() != SEMICOLON) {
            num = expression();
            accept(SEMICOLON);
        }
        else {
            accept(SEMICOLON);
        }
        exitingDEBUG("returnStatement");
        return 0;
	}
	
	int TCparser::whileStatement(){
        enteringDEBUG("whileStatement");
        accept(WHILE);
        accept(LPAREN);
        num = expression();
        accept(RPAREN);
        num = statement();
        exitingDEBUG("whileStatement");
        return 0;
	}
	
	int TCparser::readStatement(){
        enteringDEBUG("readStatement");
        accept(READ);
        accept(LPAREN);
        accept(ID);
        while (buff->getTokenType() == COMMA) {
            accept(COMMA);
            accept(ID);
        }
        accept(RPAREN);
        accept(SEMICOLON);
        exitingDEBUG("readStatement");
        return 0;
	}
	
	int TCparser::writeStatement(){
        enteringDEBUG("writeStatement");
        accept(WRITE);
        accept(LPAREN);
        num = actualParameters();
        accept(RPAREN);
        accept(SEMICOLON);
        exitingDEBUG("writeStatement");
        return 0;
	}
	
	int TCparser::newlineStatement(){
        enteringDEBUG("newlineStatement");
        accept(NEWLINE);
        accept(SEMICOLON);
        exitingDEBUG("newlineStatement");
        return 0;
	}
	
	int TCparser::expression(){
        enteringDEBUG("expression");
        num = relopExpression();
        while(buff->getTokenType() == ASSIGNOP){
            buff = scanner->getToken();
			num = relopExpression();
            //what to do with the assign operator
            //accept(buff);
        }
        
        exitingDEBUG("expression");
        return 0;
	}
	
	int TCparser::relopExpression(){
        enteringDEBUG("relopExpression");
        num = simpleExpression();
        while(buff->getTokenType() == RELOP){
            buff = scanner->getToken();
			num = simpleExpression();
            //what to do with the assign operator
            //accept(buff);
        }
        
        exitingDEBUG("relopExpression");
        return 0;
	}
	
	int TCparser::simpleExpression(){
        enteringDEBUG("simpleExpression");
        num = term();
        while(buff->getTokenType() == ADDOP){
            buff = scanner->getToken();
			num = term();
            //what to do with the assign operator
            //accept(buff);
        }
       
        exitingDEBUG("simpleExpression");
        return 0;
	}
	
	int TCparser::term(){
        enteringDEBUG("term");
        num = primary();
        while(buff->getTokenType() == MULOP){
            buff = scanner->getToken();
			num = primary();
            //what to do with the assign operator
            //accept(buff);
        }
        
        exitingDEBUG("term");
        return 0;
	}
	
	int TCparser::primary(){
        enteringDEBUG("primary");
        if(buff->getTokenType() == ID) {
            buff = scanner->getToken();
            if(buff->getTokenType() == LPAREN) {
                num = functionCall();
            }
        }
        else if(buff->getTokenType() == NUMBER) {
            buff = scanner->getToken();
        }
        else if(buff->getTokenType() == STRING) {
            buff = scanner->getToken();
        }
        else if(buff->getTokenType() == CHARLITERAL) {
            buff = scanner->getToken();
        }
        else if(buff->getTokenType() == LPAREN) {
            accept(LPAREN);
            num = expression();
            accept(RPAREN);
        }
        else if(buff->getTokenType() == ADDOP || buff->getTokenType() == NOT) {
            buff = scanner->getToken();
            num = primary();
        }
        else {
            reportSYNTAX_ERROR(scanner, "primary expected");
            exit(EXIT_FAILURE);
        }
        exitingDEBUG("primary");
        return 0;
	}
	
	int TCparser::functionCall(){
	    enteringDEBUG("functionCall");
        accept(LPAREN);
        if(buff->getTokenType() != RPAREN) {
            num = actualParameters();
            accept(RPAREN);
        }
        else {
            accept(RPAREN);
        }
        exitingDEBUG("functionCall");
        return 0;
	}
	
	int TCparser::actualParameters(){
        enteringDEBUG("actualParameters");
	    num = expression();
	    while(buff->getTokenType() == COMMA){
	        accept(COMMA);
	        num = expression();
	    }
        exitingDEBUG("actualParameters");
        return 0;
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
}