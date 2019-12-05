#ifndef TCPARSER_H
#define TCPARSER_H

#include "TClexer.h"
#include "TCtoken.h"
#include "TCtokens.h"
#include "AbstractSyntax.h"
//#include "ASabstractSyntax.h"
//#include "ASstatement.h"
//#include "ASexpression.h"
//#include "ASdefinition.h"
#define MAX_DEFINITIONS 500
#define MAX_ARGS 500
#define MAX_EXPRESSION 500
#define MAX_ID 500
#define MAX_STATES 500
#define L_VAR_MAX 500

namespace toycalc{

class TCparser {
    public:
    TCparser(TClexer* s);
    ASabstractSyntax* parse();

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



    ASabstractSyntax* toyCProgram();
    ASdefinition* definition();
    TCtoken* type();
    ASdefinition* functionDefinition(int, TCtoken*);
    int functionHeader(ASdefinition*[]);
    ASstatement* functionBody();
    int formalParamList(ASdefinition*[]);
    ASstatement* statement();
    ASstatement* expressionStatement();
    ASstatement* breakStatement();
    ASstatement* compoundStatement();
    ASstatement* ifStatement();
    ASstatement* nullStatement();
    ASstatement* returnStatement();
    ASstatement* whileStatement();
    ASstatement* readStatement();
    ASstatement* writeStatement();
    ASstatement* newlineStatement();
    ASexpression* expression();
    ASexpression* relopExpression();
    ASexpression* simpleExpression();
    ASexpression* term();
    ASexpression* primary();
    int functionCall(ASexpression*[]);
    int actualParameters(ASexpression*[]);

    void accept(int);
};

}
#endif
