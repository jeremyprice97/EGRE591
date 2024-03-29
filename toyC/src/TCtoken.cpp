#include <iostream>

#include "TCtoken.h"
#include "TCtokens.h"

/*Provided by Dr. Resler, expanded to include more */

namespace toycalc {

  TCtoken::TCtoken() { tokenType = NONE; }
  TCtoken::TCtoken(int t) { tokenType = t; lexeme = ""; }
  TCtoken::TCtoken(int t, std::string s) { tokenType = t; lexeme = s; }

  int TCtoken::getTokenType() { return tokenType; }
  std::string TCtoken::getLexeme() { return lexeme; }

  std::string TCtoken::toString() {
    std::string str="";
    switch (tokenType) {
    case ID:          	  str += "(ID,"+lexeme+")";    			break;
    case NUMBER:      	  str += "(NUMBER,"+lexeme+")"; 		break;
    case ADDOP:       	  str += "(ADDOP,"+lexeme+")"; 			break;
    case MULOP:       	  str += "(MULOP,"+lexeme+")"; 			break;
    case RELOP:       	  str += "(RELOP,"+lexeme+")"; 			break;
    case LPAREN:      	  str += "LPAREN";             			break;
    case ASSIGNOP:    	  str += "ASSIGNOP";            		break;
    case SEMICOLON:   	  str += "SEMICOLON";          			break;
    case COLON:       	  str += "COLON";              			break;
    case RPAREN:      	  str += "RPAREN";             			break;
	case LCURLY:	 	  str += "LCURLY";						break;
	case RCURLY:	  	  str += "RCURLY";						break;
	case LBRACKET:	  	  str += "LBRACKET";					break;
	case RBRACKET:	  	  str += "RBRACKET";					break;
	case NOT:		  	  str += "NOT";							break;
	case COMMA:			  str += "COMMA";						break;
    case EOFILE:      	  str += "EOF";                			break;
    case NONE:        	  str += "NONE";               			break;
    case WRITE:       	  str += "WRITE";              			break;
    case READ:        	  str += "READ";               			break;
    case IF:          	  str += "IF";                 			break;
    case THEN:        	  str += "THEN";               			break;
	case INT:		  	  str += "INT";			 				break;
	case CHAR:		  	  str += "CHAR";						break;
	case RETURN:	  	  str += "RETURN";						break;
	case FOR:		  	  str += "FOR";							break;
	case ELSE:		  	  str += "ELSE";						break;
	case DO:		  	  str += "DO";							break;
	case WHILE:		  	  str += "WHILE";						break;
	case SWITCH:	  	  str += "SWITCH";						break;
	case CASE:		  	  str += "CASE";						break;
	case DEFAULT:	  	  str += "DEFAULT";						break;
	case CONTINUE:	  	  str += "CONTINUE";					break;
	case BREAK:		  	  str += "BREAK";						break;
	case NEWLINE:	  	  str += "(NEWLINE,"+lexeme+")";		break;
	case CHARLITERAL: 	  str += "(CHARLITERAL,"+lexeme+")";	break;
	case STRING:	  	  str += "(STRING,"+lexeme+")";			break;
    default:        	  str += "[error token]";        		break; 
    }
    return str;
  }
  
}
