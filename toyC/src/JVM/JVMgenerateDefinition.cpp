#include <iostream>
#include "ASdefinition.h"
#include "ASfuncdef.h"
#include "ASvarDef.h"
#include "JVMgenerateDefinition.h"

#include "JVMtargetCode.h"

#include "JVMgenerateStatement.h"
#include "JVMgenerateExpression.h"
#include "JVMgenUtils.h"
#include "JVMgenGlobals.h"

#include "codeLabel.h"

#include "GOTO.h"
#include "IFNE.h"
#include "INVOKESPECIAL.h"
#include "INVOKEVIRTUAL.h"
#include "LDC.h"

namespace toycalc {

  void JVMgenerateDefinition::genDefinition(ASdefinition *ast,JVMtargetCode *tc) {
    enum defType dtype = ast->getType();
	if(dtype==funcDef) {
		ASfuncDef *fd = dynamic_cast<ASfuncDef*>(ast);
		ASstatement *statement = fd->getStatement();
		JVMgenerateStatement::genStatement(statement, tc);
		//std::cout << "def end" << std::endl;
	} else if (dtype == varDef) {
		
	}
  }
}
