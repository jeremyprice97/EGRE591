
#include <iostream>

#include "ASprogram.h"
#include "TCoutput.h"

namespace toycalc{

  ASprogram::ASprogram(std::string n, ASdefinition* defs[], int num) {
    for (int i=0; i < num; i++) definitionList[i] = defs[i];
    name = n; numDefinitions = num;
  }

  std::string ASprogram::getName() { return name; }
  ASdefinition** ASprogram::getDefinitionList() { return definitionList; }
  ASdefinition* ASprogram::getDefinition(int n) { return definitionList[n]; }
  int ASprogram::getNumDefinitions() { return numDefinitions; }
  
  std::string ASprogram::toString() {
    if (numDefinitions==0) return "prog([])";
    std::string s = "prog(\n";
    indent();
    s += spaces() + "sourceCodeFile(" + name + "),\n";
    s += spaces() + "[\n";
    indent();
	s += spaces();
    if (numDefinitions > 0) {
      s += (definitionList[0]->toString());
      for (int i=1; i < numDefinitions; i++)
        s += ",\n"+spaces()+definitionList[i]->toString();
    }
    outdent();
    s += "\n"+spaces() + "]\n";
    outdent();
    s += spaces() + ")\n";
    return s;
  }

}
