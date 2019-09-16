#include <iostream>

#include "TCtoken.h"
#include "TCtokens.h"

namespace toycalc {

  TCtoken::TCtoken() { tokenType = NONE; }
  TCtoken::TCtoken(int t) { tokenType = t; lexeme = ""; }
  TCtoken::TCtoken(int t, std::string s) { tokenType = t; lexeme = s; }

  int TCtoken::getTokenType() { return tokenType; }
  std::string TCtoken::getLexeme() { return lexeme; }

  std::string TCtoken::toString() {
    std::string str="";
    switch (tokenType) {
    case ID:        str += "(ID,"+lexeme+")";    break;
    case NUM:       str += "(NUM,"+lexeme+")";   break;
    case ADDOP:     str += "(ADDOP,"+lexeme+")"; break;
    case MULOP:     str += "(MULOP,"+lexeme+")"; break;
    case RELOP:     str += "(RELOP,"+lexeme+")"; break;
    case AND:       str += "AND";                break;
    case OR:        str += "OR";                 break;
    case LPAREN:    str += "LPAREN";             break;
    case ASSIGN:    str += "ASSIGN";             break;
    case SEMICOLON: str += "SEMICOLON";          break;
    case COLON:     str += "COLON";              break;
    case RPAREN:    str += "RPAREN";             break;
    case EOFILE:    str += "EOF";                break;
    case NONE:      str += "NONE";               break;
    case WRITE:     str += "WRITE";              break;
    case READ:      str += "READ";               break;
    case IF:        str += "IF";                 break;
    case THEN:      str += "THEN";               break;
    case GOTO:      str += "GOTO";               break;
    case SKIP:      str += "SKIP";               break;
    default:        str += "[error token]";        break; 
    }
    return str;
  }
  
}
