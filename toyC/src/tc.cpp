#include <iostream>
#include <sstream>
#include <vector>

#include "TCtoken.h"
#include "TClexer.h"
#include "TCglobals.h"
#include "TCtokens.h"
#include "TCparser.h"

#include "AbstractSyntax.h"

#include "CGcodeGenerator.h"
#include "CGtargetCode.h"
#include "JVMcodeGenerator.h"
#include "JVMtargetCode.h"

/*Provided by Dr. Resler*/

using namespace toycalc;
using namespace std;

void processCommandLine(int, char *[]);
void printUsageMessage();
std::string getProgramName(std::string);

int main(int argc, char *argv[]) {
    try {
        processCommandLine(argc,argv);
        TClexer *scanner = new TClexer(inputFileName);  //scanner and parser
        TCparser *parser = new TCparser(scanner);   //parser only
        //int tok;                                    //scanner only
		ASabstractSyntax* p = NULL;                 //parser only
        //    turnVerboseOn();
        p = parser->parse();                      //parser only
        if(verbose) cout << p->toString();                    //parser only
        CGcodeGenerator *cg = new JVMcodeGenerator();
        CGtargetCode* tc = cg->generateCode(p);
        if(verbose) tc->writeCode(tc,targetFileName);

        //while ((tok=scanner->getToken()->getTokenType()) != EOFILE) ;     //scanner only
    } catch(...) {
        std::cerr << "ERROR: scanning failed" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void processCommandLine(int argc, char *argv[]) {
    switch(argc) {
        case 1: printUsageMessage(); exit(EXIT_FAILURE);
        case 2: if (argv[1][0] != '-') {
                inputFileName = argv[1];
                break;
            } else {
                printUsageMessage(); exit(EXIT_SUCCESS);
            };
        case 3: if (argv[1][0]=='-' && argv[1][1]=='v') {
                turnVerboseOn();
                inputFileName = argv[2];
                break;
            } else {
                printUsageMessage(); exit(EXIT_FAILURE);
            }
        default: printUsageMessage();
    }
    outputClassFileName = getProgramName(inputFileName);
    targetFileName = outputClassFileName+"."+ASM_FILE_EXTENSION;
}
vector<string> split (const string &s, char delim) {
    vector<string> result;
    stringstream ss (s);
    string item;
    while (getline (ss, item, delim)) {
        result.push_back (item);
    }
    return result;
}

std::string getProgramName(std::string s) {
    vector<string> strs = split(s,'/');
    return split(strs[strs.size()-1],'.')[0];
}

void printUsageMessage() {
    std::cout << "Usage: tc [-v] input_file" << std::endl;
    std::cout << "  where -v means verbose output" << std::endl;
}

