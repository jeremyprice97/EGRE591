#include <iostream>
#include <fstream>

#include "TCtoken.h"
#include "TClexer.h"
#include "TCglobals.h"
#include "TCtokens.h"
#include "TCoutput.h"
/*Provided by Dr. Resler, expanded to include more 
The changes that were made are noted to the side*/

namespace toycalc {

  static char charBuff;
  static std::string line;
  static unsigned int pos;
  //static int lineNum = 0;
  static std::string lexeme = ""; 
  static char EOFCHAR = '\0'; // arbitrary non-printing char
  static std::ifstream infile;
  
  char getChar();
  std::string getNextLine();
  bool isInAlphabet(char);
  bool equalIgnoreCase(std::string, std::string);
  int blockCommentCount = 0;
    
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
      if (charBuff == '.') {									/*start of new code added my Matthew and Jeremy*///decimal point
        lexeme += charBuff; charBuff = getChar();
        //if (!isdigit(charBuff))
          //reportWARNING("","state 1: illegal character "+lexeme+" ignored 1");
        //          reportWARNING("","illegal character '"+charBuff+"' ignored");
		if(isdigit(charBuff)){
		  do {
            lexeme += charBuff; charBuff = getChar();
          } while(isdigit(charBuff));
		  if(charBuff == 'E') {									//E with digit for exponent
			lexeme += charBuff; charBuff = getChar();
			if(isdigit(charBuff)){								//digit(s) after E
				do {
					lexeme += charBuff; charBuff = getChar();
				} while(isdigit(charBuff));
			}
			else if(charBuff == '+' || charBuff == '-'){				//+ or - after E
				lexeme += charBuff; charBuff = getChar();
				if(isdigit(charBuff)){							//digit(s) after + or -
					do {
						lexeme += charBuff; charBuff = getChar();
					} while(isdigit(charBuff));
				}
				else{
					reportWARNING("","state 3: illegal character "+lexeme+" ignored 1");
					t = new TCtoken(-1);
					return t;
				}
			} else {
				reportWARNING("","state 4: illegal character "+lexeme+" ignored 1");
				t = new TCtoken(-1);
				return t;
			}
		  }
		  /*else{
			reportWARNING("","state 5: illegal character "+lexeme+" ignored 1");
		  }*/
		} else{
			reportWARNING("","state 8: illegal character "+lexeme+" ignored 1"); charBuff = getChar();
			t = new TCtoken(-1);
			return t;
		}
      }
	  else if(charBuff == 'E') {								//E after digits, no decimal point
		    lexeme += charBuff; charBuff = getChar();
		    if(isdigit(charBuff)){									//digit(s) after E
				do {
					lexeme += charBuff; charBuff = getChar();
				} while(isdigit(charBuff));
			}
			else if(charBuff == '+' || charBuff == '-'){				//+ or - after E
				lexeme += charBuff; charBuff = getChar();
				if(isdigit(charBuff)){							//digit(s) after + or -
					do {
						lexeme += charBuff; charBuff = getChar();
					} while(isdigit(charBuff));
				}
				else{
					reportWARNING("","state 6: illegal character "+lexeme+" ignored 1");
					t = new TCtoken(-1);
					return t;
				}
			} else {
				reportWARNING("","state 7: illegal character "+lexeme+" ignored 1");
				t = new TCtoken(-1);
				return t;
			}
	  }															/*end of new code added my Matthew and Jeremy*/
	  /*else{
			reportWARNING("","illegal character "+lexeme+" ignored 1");
			t = new TCtoken(-1);
			return t;
	  }*/
      t = new TCtoken(NUMBER,lexeme);
    } else if (isalpha(charBuff)) {							//keywords or IDs
      do {													/*start of new code added my Matthew and Jeremy*/
        lexeme += charBuff; charBuff = getChar();			/*Various keywords that were not alrady provided were added*/
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
	  else if (equalIgnoreCase(lexeme,"NEWLINE"))
        t = new TCtoken(NEWLINE,"newline word");
      else {
        t = new TCtoken(ID,lexeme);
      }													/*end of changes made to code added my Matthew and Jeremy*/
    } else {
      lexeme += charBuff;
      switch (charBuff) {
            case '+': t = new TCtoken(ADDOP,"+"); charBuff = getChar(); break;
            case '-': t = new TCtoken(ADDOP,"-"); charBuff = getChar(); break;
			case '|': charBuff = getChar();						/*this case added my Matthew and Jeremy*/
					  if (charBuff == '|') {
						  t = new TCtoken(ADDOP,"||"); charBuff = getChar(); break; 
					  }
					  else{
						  reportWARNING("","illegal character "+lexeme+" ignored 1");
						  t = new TCtoken(-1);
						  break;
					  }
            case '*': t = new TCtoken(MULOP,"*"); charBuff = getChar(); break;
            case '%': t = new TCtoken(MULOP,"%"); charBuff = getChar(); break; 			/*this case added my Matthew and Jeremy*/
			case '&': charBuff = getChar();						/*this case added my Matthew and Jeremy*/
					  if (charBuff == '&') {
						  t = new TCtoken(MULOP,"&&"); charBuff = getChar(); break;
					  }
					  else{
						  reportWARNING("","illegal character "+lexeme+" ignored 1");
						  t = new TCtoken(-1);
						  break;
					  }					  
			case '/': t = new TCtoken(MULOP,"/"); charBuff = getChar();	break;		/*this case modified my Matthew and Jeremy*/

			case '\'': charBuff = getChar();									/*this case added my Matthew and Jeremy*/
					  if (charBuff == '\n') {
						  reportWARNING("","char state 1: illegal character "+lexeme+" ignored 1");
						  t = new TCtoken(-1);
						  break;
					  } else if (charBuff == '\'') {
						  lexeme += charBuff;
						  t = new TCtoken(CHARLITERAL,lexeme); charBuff = getChar(); break;
					  } else {
						  lexeme += charBuff; charBuff = getChar();
						  if (charBuff == '\'') {
							  lexeme += charBuff;
							  t = new TCtoken(CHARLITERAL,lexeme); charBuff = getChar(); break;
						  } else {
							  reportWARNING("","char state 2: illegal character "+lexeme+" ignored 1");
							  t = new TCtoken(-1);
							  break;
						  }
					  }
			case '\"': charBuff = getChar();							/*this case added my Matthew and Jeremy*/
					  if (charBuff == '\n') {
						  reportWARNING("","string state 1: illegal character "+lexeme+" ignored 1");
						  t = new TCtoken(-1);
						  break;
					  } else if (charBuff == '\"') {
						  lexeme += charBuff;
						  t = new TCtoken(STRING,lexeme); charBuff = getChar(); break;
					  } else {
						  //lexeme += charBuff; charBuff = getChar();
						  do {
							lexeme += charBuff; charBuff = getChar();
						  } while(charBuff != '\"');
						  lexeme += charBuff;
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
			case '{': t = new TCtoken(LCURLY); charBuff = getChar(); break;		/*this case added my Matthew and Jeremy*/
            case '}': t = new TCtoken(RCURLY); charBuff = getChar(); break;		/*this case added my Matthew and Jeremy*/
			case '[': t = new TCtoken(LBRACKET); charBuff = getChar(); break;		/*this case added my Matthew and Jeremy*/
            case ']': t = new TCtoken(RBRACKET); charBuff = getChar(); break;		/*this case added my Matthew and Jeremy*/
			
            case '=': charBuff = getChar();
                      if (charBuff == '=') {
                          t = new TCtoken(RELOP,"=="); charBuff = getChar();
                      } else
                          t = new TCtoken(ASSIGNOP);
                      break;
			case '!': charBuff = getChar();									/*this case added my Matthew and Jeremy*/
                      if (charBuff == '=') {
                          t = new TCtoken(RELOP,"!="); charBuff = getChar();
                      } else
                          t = new TCtoken(NOT);
                      break;		  
            case ',': t = new TCtoken(COMMA); charBuff = getChar(); break;		/*this case added my Matthew and Jeremy*/
            case ';': t = new TCtoken(SEMICOLON); charBuff = getChar(); break;
            case ':': t = new TCtoken(COLON);     charBuff = getChar(); break;
			case '\n': t = new TCtoken(NEWLINE,"/n");     charBuff = getChar(); break;			/*this case added my Matthew and Jeremy*/
            default: // shouldn't happen!
              t = new TCtoken(NONE); break;
            }
        }
        if (verbose) reportDEBUG("  ","scanner",t->toString());
        return t;
																									//added this } because something didn't match up
  }
  
  std::string TClexer::getLine() { return line; }
  std::string TClexer::getLexeme() { return lexeme; }
  int TClexer::getPos() { return pos + 1; }
  int TClexer::getLineNum() { return lineNum; }

  char getChar() {
    do {
      if (infile.eof()) return EOFCHAR;
      if (line.empty() || pos > line.length()) line = getNextLine();
      char ch = line[pos];
      if(ch == '\0') {
          line = getNextLine();
          ch = line[pos];
      }
      if ( ((line[0] == '/') && (line[1] == '/')) || ((ch == '/') && (line[pos+1] == '/')) ) {
          line = getNextLine();
          ch = line[pos];
          continue;
      }
      if((ch == '/') && (line[pos+1] == '*')) {									//this case added my Matthew and Jeremy
          blockCommentCount++;
          pos += 2;
          while(!((line[pos] == '*') && (line[pos+1] == '/')) || blockCommentCount>1) {
              if((line[pos] == '/') && (line[pos+1] == '*')) {
                  blockCommentCount++;
                  pos++;
              }
              else if((line[pos] == '*') && (line[pos+1] == '/')) {
                  blockCommentCount--;
                  pos++;
              }
              pos++;
              if (line.empty() || pos > line.length()) line = getNextLine();
          }
          blockCommentCount--;
          pos += 2;
      }
      if (isInAlphabet(ch) || isspace(ch)) break;
        
      reportWARNING("","illegal character "+lexeme+" ignored 2");
	  //printf("%c",ch);
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

bool isInAlphabet(char ch) {									/*various characters added my Matthew and Jeremy*/
  return ( isalpha(ch) || isdigit(ch) ||
  	 (ch == '+') || (ch == '-') || (ch == '*') || (ch == '/') ||
  	 (ch == '<') || (ch == '>') || (ch == '(') || (ch == ')') || 
     (ch == '=') || (ch == ';') || (ch == ':') || (ch == '%') ||
	 (ch == '{') || (ch == '}') || (ch == '[') || (ch == ']') ||
	 (ch == '\'') || (ch == '\"') || (ch == '!') || (ch == '&') ||
	 (ch == '|') || (ch == ',') || (ch == '\n') || (ch == '.')); 
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
