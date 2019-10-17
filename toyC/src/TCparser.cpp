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

        return 0;
	}
	
	int TCparser::statement(){

        return 0;
	}
	
	int TCparser::expressionStatement(){

        return 0;
	}
	
	int TCparser::breakStatement(){

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
        accept(SEMICOLON);
        return 0;
	}
	
	int TCparser::returnStatement(){
        accept(RETURN);
        if(buff->getTokenType() != SEMICOLON) {
            num = expression();
            accept(SEMICOLON);
        }
        else {
            accept(SEMICOLON);
        }
        return 0;
	}
	
	int TCparser::whileStatement(){
        accept(WHILE);
        accept(LPAREN);
        num = expression();
        accept(RPAREN);
        num = statement();

        return 0;
	}
	
	int TCparser::readStatement(){
        accept(READ);
        accept(LPAREN);
        accept(ID);
        while (buff->getTokenType() == COMMA) {
            accept(COMMA);
            accept(ID);
        }
        accept(RPAREN);
        accept(SEMICOLON);
        return 0;
	}
	
	int TCparser::writeStatement(){
        accept(WRITE);
        accept(LPAREN);
        num = actualParameters();
        accept(RPAREN);
        accept(SEMICOLON);
        return 0;
	}
	
	int TCparser::newLineStatement(){
        accept(NEWLINE);
        accept(SEMICOLON);
        return 0;
	}
	
	int TCparser::expression(){
        num = relopExpression();
        if(buff->getTokenType() == ASSIGNOP){
            buff = scanner->getToken();
            //what to do with the assign operator
            //accept(buff);
        }
        num = relopExpression();
        return 0;
	}
	
	int TCparser::relopExpression(){
        num = simpleExpression();
        if(buff->getTokenType() == RELOP){
            buff = scanner->getToken();
            //what to do with the assign operator
            //accept(buff);
        }
        num = simpleExpression();
        return 0;
	}
	
	int TCparser::simpleExpression(){
        num = term();
        if(buff->getTokenType() == ADDOP){
            buff = scanner->getToken();
            //what to do with the assign operator
            //accept(buff);
        }
        num = term();
        return 0;
	}
	
	int TCparser::term(){
        num = primary();
        if(buff->getTokenType() == MULOP){
            buff = scanner->getToken();
            //what to do with the assign operator
            //accept(buff);
        }
        num = primary();
        return 0;
	}
	
	int TCparser::primary(){

        return 0;
	}
	
	int TCparser::functionCall(){
        accept(LPAREN);
        if(buff->getTokenType() != RPAREN) {
            num = actualParameters();
            accept(RPAREN);
        }
        else {
            accept(RPAREN);
        }
        return 0;
	}
	
	int TCparser::actualParameters(){
	    num = expression();
	    while(buff->getTokenType() == COMMA){
	        accept(COMMA);
	        num = expression();
	    }
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