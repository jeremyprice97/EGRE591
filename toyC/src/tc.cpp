#include <iostream>

#include "TCtoken.h"
#include "TClexer.h"
#include "TCglobals.h"
#include "TCtokens.h"
#include "TCparser.h"

/*Provided by Dr. Resler*/

using namespace toycalc;
using namespace std;

void processCommandLine(int, char *[]);
void printUsageMessage();

int main(int argc, char *argv[]) {
    try {
        processCommandLine(argc,argv);
        TClexer *scanner = new TClexer(inputFileName);  //scanner
        TCparser *parser = new TCparser(scanner);   //parser
        int tok;
        //    turnVerboseOn();
        tok = parser->parse();                      //parser
        //while ((tok=scanner->getToken()->getTokenType()) != EOFILE) ;     //scanner
    } catch(...) {
        std::cerr << "ERROR: scanning failed" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void processCommandLine(int argc, char *argv[]) {
    switch(argc) {
        case 1: printUsageMessage(); break;
        case 2: if (argv[1][0] != '-')
                inputFileName = argv[1];
            else
                printUsageMessage();
            break;
        case 3: if (argv[1][0]=='-' && argv[1][1]=='v') {
                turnVerboseOn();
                inputFileName = argv[2];
            } else printUsageMessage();
            break;

        default: printUsageMessage();
    }
}

void printUsageMessage() {
    std::cout << "Usage: tc [-v] input_file" << std::endl;
    std::cout << "  where -v means verbose output" << std::endl;
}

