#include <iostream>
#include <fstream>

#include "TCtoken.h"
#include "TClexer.h"
#include "TCglobals.h"
#include "TCtokens.h"
#include "TCoutput.h"

namespace toycalc {

  static char charBuff;
  static std::string line;
  static int pos;
  static int lineNum = 0;
  static std::string lexeme = ""; 
  static char EOFCHAR = '\0'; // arbitrary non-printing char
  static std::ifstream infile;
  
  char getChar();
  std::string getNextLine();
  bool isInAlphabet(char);
  bool equalIgnoreCase(std::string, std::string);
    
  TClexer::TClexer(std::string fname) {
    inputFileName = fname;
    line = ""; pos = 0;
    infile.open(inputFileName);
    if(infile.fail()) {
      std::cerr << "ERROR: input file not found" << std::endl;
      exit (EXIT_FAILURE);
    }
    charBuff = getChar(); 
  }
  
  TCtoken* TClexer::getToken() {
    lexeme = ""; TCtoken* t;

    while (isspace(charBuff) && (charBuff != EOFCHAR)) charBuff = getChar();
    if (charBuff == EOFCHAR) {
            t = new TCtoken(EOFILE); 
            if (verbose) reportDEBUG("  ","scanner",t->toString());
            return t;
    } else if (isdigit(charBuff)) {								//digit(s) for all numbers
      do {
        lexeme += charBuff; charBuff = getChar();
      } while(isdigit(charBuff));
      if (charBuff == '.') {									//decimal point
        lexeme += charBuff; charBuff = getChar();
        if (!isdigit(charBuff))
          reportWARNING("","illegal character ignored 1");
        //          reportWARNING("","illegal character '"+charBuff+"' ignored");
          do {
            lexeme += charBuff; charBuff = getChar();
          } while(isdigit(charBuff));
		  if(charBuff == 'E') {									//E with digit for exponent
			lexeme += charBuff; charBuff = getChar();
			if(isdigit(charBuff){								//digit(s) after E
				do {
					lexeme += charBuff; charBuff = getChar();
				} while(isdigit(charBuff));
			}
			if(charBuff == '+' || charBuff == '-'){				//+ or - after E
				lexeme += charBuff; charBuff = getChar();
				if(isdigit(charBuff){							//digit(s) after + or -
					do {
						lexeme += charBuff; charBuff = getChar();
					} while(isdigit(charBuff));
				}
				else{
					reportWARNING("","illegal character ignored 1");
				}
			} else {
				reportWARNING("","illegal character ignored 1");
			}
		  }
		  else{
			reportWARNING("","illegal character ignored 1");
		  }
      }
	  else if(charBuff == 'E') {								//E after digits, no decimal point
		    lexeme += charBuff; charBuff = getChar();
		    if(isdigit(charBuff){									//digit(s) after E
				do {
					lexeme += charBuff; charBuff = getChar();
				} while(isdigit(charBuff));
			}
			if(charBuff == '+' || charBuff == '-'){				//+ or - after E
				if(isdigit(charBuff){							//digit(s) after + or -
					do {
						lexeme += charBuff; charBuff = getChar();
					} while(isdigit(charBuff));
				}
				else{
					reportWARNING("","illegal character ignored 1");
				}
			}
	  }
	  else{
			reportWARNING("","illegal character ignored 1");
	  }
      t = new TCtoken(NUMBER,lexeme);
    } else if (isalpha(charBuff)) {							//keywords or IDs
      do {
        lexeme += charBuff; charBuff = getChar();
      } while(isalpha(charBuff) || isdigit(charBuff));
 
      if (equalIgnoreCase(lexeme,std::string("INT")))
        t = new TCtoken(INT);
      else if (equalIgnoreCase(lexeme,"CHAR"))
        t = new TCtoken(CHAR);
      else if (equalIgnoreCase(lexeme,"RETURN"))
        t = new TCtoken(RETURN);
      else if (equalIgnoreCase(lexeme,"IF"))
        t = new TCtoken(IF);
      else if (equalIgnoreCase(lexeme,"ELSE"))
        t = new TCtoken(ELSE);
      else if (equalIgnoreCase(lexeme,"FOR"))
        t = new TCtoken(FOR);
      else if (equalIgnoreCase(lexeme,"DO"))
        t = new TCtoken(DO);
      else if (equalIgnoreCase(lexeme,"WHILE"))
        t = new TCtoken(WHILE);
	  else if (equalIgnoreCase(lexeme,"SWITCH"))
        t = new TCtoken(SWITCH);
	  else if (equalIgnoreCase(lexeme,"CASE"))
        t = new TCtoken(CASE);
	  else if (equalIgnoreCase(lexeme,"DEFAULT"))
        t = new TCtoken(DEFAULT);
	  else if (equalIgnoreCase(lexeme,"WRITE"))
        t = new TCtoken(WRITE);
	  else if (equalIgnoreCase(lexeme,"READ"))
        t = new TCtoken(READ);
	  else if (equalIgnoreCase(lexeme,"CONTINUE"))
        t = new TCtoken(CONTINUE);
	  else if (equalIgnoreCase(lexeme,"BREAK"))
        t = new TCtoken(BREAK);
	  else if (equalIgnoreCase(lexeme,"NEWLINE"))					//probably not needed
        t = new TCtoken(NEWLINE);
      else {
        t = new TCtoken(ID,lexeme);
      }
    } else {
      lexeme += charBuff;
      switch (charBuff) {
            case '+': t = new TCtoken(ADDOP,"+"); charBuff = getChar(); break;
            case '-': t = new TCtoken(ADDOP,"-"); charBuff = getChar(); break;
			case '|': charBuff = getChar();
					  if (charBuff == '|') {
						  t = new TCtoken(ADDOP,"||"); charBuff = getChar(); break; 
					  }
					  else{
						  reportWARNING("","illegal character ignored 1");
					  }
            case '*': t = new TCtoken(MULOP,"*"); charBuff = getChar(); break;
            case '%': t = new TCtoken(MULOP,"%"); charBuff = getChar(); break;
			case '&': charBuff = getChar();
					  if (charBuff == '&') {
						  t = new TCtoken(MULOP,"&&"); charBuff = getChar(); break;
					  }
					  else{
						  reportWARNING("","illegal character ignored 1");
					  }					  
			case '/': charBuff = getChar();								//put forward slash here
					  if (charBuff == '*') {
						  do {
							charBuff = getChar();
							if (charBuff == '*') {
								do {
									charBuff = getChar();
								} while(charBuff == '*');
								
								if (charBuff == '/') {
									break;
								}
							}
						  } while(charBuff != EOFCHAR);
					  } else
                          t = new TCtoken(MULOP,"/");
                      break;
			case '\'': charBuff = getChar();								//put char literal here
					  if (charBuff == '\n') {
						  reportWARNING("","illegal character ignored 1");
						  break;
					  } else if (charBuff == '\'') {
						  t = new TCtoken(CHARLITERAL,"\0"); charBuff = getChar(); break;
					  } else {
						  lexeme += charBuff; charBuff = getChar();
						  if (charBuff == '\'') {
							  t = new TCtoken(CHARLITERAL,lexeme); charBuff = getChar(); break;
						  } else {
							  reportWARNING("","illegal character ignored 1");
							  break;
						  }
					  }
			case '\"': charBuff = getChar();								//put string here
					  if (charBuff == '\n') {
						  reportWARNING("","illegal character ignored 1");
						  break;
					  } else if (charBuff == '\"') {
						  t = new TCtoken(STRING,"\0"); charBuff = getChar(); break;
					  } else {
						  lexeme += charBuff; charBuff = getChar();
						  do {
							lexeme += charBuff; charBuff = getChar();
						  } while(charBuff != "\"");
						  t = new TCtoken(STRING,lexeme); charBuff = getChar(); break;
					  }
			
            case '<': charBuff = getChar();
                      if (charBuff == '=') {
                          t = new TCtoken(RELOP,"<="); charBuff = getChar();
                      } else
                          t = new TCtoken(RELOP,"<");
                      break;
            case '>': charBuff = getChar();
                      if (charBuff == '=') {
                          t = new TCtoken(RELOP,">="); charBuff = getChar();
                      } else
                          t = new TCtoken(RELOP,">");
                      break;
					  
            case '(': t = new TCtoken(LPAREN); charBuff = getChar(); break;
            case ')': t = new TCtoken(RPAREN); charBuff = getChar(); break;
			case '{': t = new TCtoken(LCURLY); charBuff = getChar(); break;
            case '}': t = new TCtoken(RCURLY); charBuff = getChar(); break;
			case '[': t = new TCtoken(LBRACKET); charBuff = getChar(); break;
            case ']': t = new TCtoken(RBRACKET); charBuff = getChar(); break;
			
            case '=': charBuff = getChar();
                      if (charBuff == '=') {
                          t = new TCtoken(RELOP,"=="); charBuff = getChar();
                      } else
                          t = new TCtoken(ASSIGN);
                      break;
			case '!': charBuff = getChar();
                      if (charBuff == '=') {
                          t = new TCtoken(RELOP,"!="); charBuff = getChar();
                      } else
                          t = new TCtoken(NOT);
                      break;		  
            case ',': t = new TCtoken(COMMA); charBuff = getChar(); break;
            case ';': t = new TCtoken(SEMICOLON); charBuff = getChar(); break;
            case ':': t = new TCtoken(COLON);     charBuff = getChar(); break;
			case '\n': t = new TCtoken(NEWLINE);     charBuff = getChar(); break;
            default: // shouldn't happen!
              t = new TCtoken(NONE);
            }
        }
        if (verbose) reportDEBUG("  ","scanner",t->toString());
        return t;
	}																								//added this } because something didn't match up
  }

  std::string TClexer::getLine() { return line; }
  std::string TClexer::getLexeme() { return lexeme; }
  int TClexer::getPos() { return pos; }
  int TClexer::getLineNum() { return lineNum; }
  
  char getChar() {
    do {
      if (infile.eof()) return EOFCHAR;
      if (line.empty() || pos > line.length()) line = getNextLine();
      char ch = line[pos];
      if ( ((ch == '/') && (line[pos+1] == '/')) || (ch == '\0') ) {
        line = getNextLine();
        ch = line[pos];
      }
      if (isInAlphabet(ch) || isspace(ch)) break;
        
      reportWARNING("","illegal character ignored 2");
      //      reportWARNING("","illegal character '"+line[pos]+"' ignored")
      pos++;
      
    } while (true);
    return line[pos++];
  }
   
std::string getNextLine() {
  std::string line;
  std::getline(infile,line);
  line = line + " ";
  pos = 0; lineNum++;
  // if (verbose) reportDEBUG("","input",lineNum+": "+line);
  return line;
}

bool isInAlphabet(char ch) {
  return ( isalpha(ch) || isdigit(ch) ||
  	 (ch == '+') || (ch == '-') || (ch == '*') || (ch == '/') ||
  	 (ch == '<') || (ch == '>') || (ch == '(') || (ch == ')') || 
         (ch == '=') || (ch == ';') || (ch == ':') ); 
}

bool compareChar(char& c1, char& c2){
  if (c1 == c2) return true;
  else if (std::toupper(c1) == std::toupper(c2)) return true;
  return false;
}

bool equalIgnoreCase(std::string str1, std::string str2){
  return ( (str1.size() == str2.size() ) &&
           std::equal(str1.begin(), str1.end(), str2.begin(), &compareChar) );
}
  
}
