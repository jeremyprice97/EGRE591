#include <iostream>

#include "TCsymTable.h"
/*Provided by Dr. Resler*/

namespace toycalc {

    std::string inputFileName;
    std::string outputClassFileName;
    std::string targetFileName;
    std::string ASM_FILE_EXTENSION = "j";
    TCsymTable *symTable = NULL; 

  //    public  AbstractSyntax ast = null; 
  //  public  TargetCode objectcode = null;

    std::string COMPILER = "toyc";
    std::string VERSION = "v1.0"; 
    std::string AUTHOR = "Jeremy Price and Matt Gelber";
	int is_output = 0;
	int is_input = 0;
	int lineNum = 0;
    bool verbose=false;

    void turnVerboseOn() { verbose = true; }
    void turnVerboseOff() { verbose = false; }
}

