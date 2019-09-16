#include <iostream>

#include "TCsymTable.h"

namespace toycalc {

    std::string inputFileName;
    std::string outputClassFileName;
    std::string targetFileName;
    std::string ASM_FILE_EXTENSION = "j";
    TCsymTable *symTable = NULL; 

  //    public  AbstractSyntax ast = null; 
  //  public  TargetCode objectcode = null;

    std::string COMPILER = "toycalc";
    std::string VERSION = "v1.0"; 
    std::string AUTHOR = "D. Resler";

    bool verbose=false;

    void turnVerboseOn() { verbose = true; }
    void turnVerboseOff() { verbose = false; }
}

