#ifndef TCPARSER_H
#define TCPARSER_H

#include "TClexer.h"
#include "TCtoken.h"
//#include "ASabstractSyntax.h"
//#include "ASstatement.h"
//#include "ASexpr.h"

namespace toycalc{

class TCparser {
    public:
    TCparser(TClexer* s);
    int parse();

    //ASabstractSyntax* parse();

    private:
    TClexer* scanner;
    TCtoken* buff;

    //ASabstractSyntax* program();
    //int statementList(ASstatement *[],int);
    //ASstatement* statement();
    //ASexpr* expr();
    //ASexpr* term();
    //ASexpr* element();
    //ASexpr* factor();


    int toyCProgram();
    int definition();
    int type();
    int functionDefinition();
    int functionHeader();
    int functionBody();
    int formalParamList();
    int statement();
    int expressionStatement();
    int breakStatement();
    int compoundStatement();
    int ifStatement();
    int nullStatement();
    int returnStatement();
    int whileStatement();
    int readStatement();
    int writeStatement();
    int newLineStatement();
    int expression();
    int relopExpression();
    int simpleExpression();
    int term();
    int primary();
    int functionCall();
    int actualParameters();

    void accept(int);
};

}
#endif
