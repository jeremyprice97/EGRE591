#include <iostream>

#include "ASprogram.h"
#include "ASstatement.h"
//#include "ASlabelState.h"
#include "JVMtargetCode.h"
#include "JVMgenerateProgram.h"
#include "JVMgenerateDefinition.h"
#include "JVMgenerateStatement.h"
#include "JVMgenGlobals.h"
#include "JVMgenUtils.h"

#include "blankLine.h"
#include "end.h"
#include "limit.h"
#include "method.h"
#include "blankComment.h"
#include "sourceFileComment.h"
#include "targetFileComment.h"
#include "timeAndSourceComment.h"
#include "blankComment.h"
#include "source.h"
#include "class_.h"
#include "super_.h"
#include "throws_.h"
#include "TCsymbol.h"

#include "TCglobals.h"
#include "ALOAD_0.h"
#include "GETSTATIC.h"
#include "INVOKESPECIAL.h"
#include "RETURN.h"
#include "DUP.h"
#include "NEW.h"
#include "RETURN.h"


namespace toycalc {

  void JVMgenerateProgram::genProgram(ASprogram *ast,JVMtargetCode *tc) {
    genIntro(tc);
    genConstructor(tc);
    genMainMethod(ast->getDefinitionList(),ast->getNumDefinitions(),tc);
  }

  void JVMgenerateProgram::genIntro(JVMtargetCode *tc) {
    gen_intro_comments(inputFileName,targetFileName,tc);
    tc->add(new blankLine());
    gen_source_directive(inputFileName, tc);
    gen_class_directive(outputClassFileName, tc);
    gen_super_directive(ROOT_CLASS, tc);
    tc->add(new blankLine());
  }

  void JVMgenerateProgram::genConstructor(JVMtargetCode *tc) {
    method *m = new method("<init>", "V");
    m->addAccessSpec("public");
    tc->add(m);
    tc->add(new limit("stack",1));
    tc->add(new limit("locals",1));
    tc->add(new ALOAD_0());
    tc->add(new INVOKESPECIAL(OBJECT_CONSTRUCTOR));
    tc->add(new RETURN());
    tc->add(new end());
    tc->add(new blankLine());
  }

  void JVMgenerateProgram::genMainMethod(ASdefinition** definitions,int num,JVMtargetCode* tc) {
    gen_main_header(tc);
    gen_stack_limit_directive(tc);
    gen_locals_limit_directive(tc);
    if (is_input)
		gen_input_stream_store(tc);
    if (is_output)
		gen_output_stream_store(tc);
    for (int i=0; i < num; i++) {
      JVMgenerateDefinition::genDefinition(definitions[i],tc);
		//std::cout << "end of defs" << std::endl;
	}
	
    tc->add(new RETURN());
    tc->add(new end());
  }

  void JVMgenerateProgram::gen_intro_comments(std::string s, std::string t, JVMtargetCode *tc) {
    tc->add(new blankComment());
    tc->add(new sourceFileComment(s));
    tc->add(new targetFileComment(t));
    tc->add(new timeAndSourceComment());
    tc->add(new blankComment());
  }
 
  void JVMgenerateProgram::gen_source_directive(std::string file, JVMtargetCode *tc) {
    tc->add(new source(file));
  }
  
  void JVMgenerateProgram::gen_class_directive(std::string file, JVMtargetCode *tc) {
    class_ *cDirective = new class_(file);
    cDirective->addAccessSpec("public");
    tc->add(cDirective);
  }

  void JVMgenerateProgram::gen_super_directive(std::string parent, JVMtargetCode *tc) {
    tc->add(new super_(parent));
  }

  void JVMgenerateProgram::gen_main_header(JVMtargetCode* tc) {
    method *m = new method("main", "V");
    m->addArg("[Ljava/lang/String;");
    m->addAccessSpec("public");
    m->addAccessSpec("static");
    tc->add(m);
  }

  void gen_throws_directive(JVMtargetCode *tc){
    tc->add(new throws_(IOEXCEPTION));
  }

  void JVMgenerateProgram::gen_output_stream_store(JVMtargetCode *tc) {
      tc->add(new GETSTATIC(OUTPUT_FIELD_SPEC,OUTPUT_DESCRIPTOR));
      JVMgenUtils::gen_ASTORE(*symTable->getSym(symTable->find("System.out")),tc);
  }

  void JVMgenerateProgram::gen_input_stream_store(JVMtargetCode *tc) {
	  tc->add(new NEW(SCANNER));
      tc->add(new DUP());
      tc->add(new GETSTATIC(INPUT_FIELD_SPEC,INPUT_DESCRIPTOR));
      tc->add(new INVOKESPECIAL(SCANNER_CONSTRUCTOR));
      JVMgenUtils::gen_ASTORE(*symTable->getSym(symTable->find("System.in")),tc);
  }

  void JVMgenerateProgram::gen_stack_limit_directive(JVMtargetCode *tc){
      tc->add(new limit("stack",10)); // arbitrary, for now
  }

  void JVMgenerateProgram::gen_locals_limit_directive(JVMtargetCode *tc){
      tc->add(new limit("locals",TCsymbol::getNextOffset())); // arbitrary, for now
  }

}