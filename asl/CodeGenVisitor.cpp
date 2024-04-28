//////////////////////////////////////////////////////////////////////
//
//    CodeGenVisitor - Walk the parser tree to do
//                     the generation of code
//
//    Copyright (C) 2020-2030  Universitat Politecnica de Catalunya
//
//    This library is free software; you can redistribute it and/or
//    modify it under the terms of the GNU General Public License
//    as published by the Free Software Foundation; either version 3
//    of the License, or (at your option) any later version.
//
//    This library is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//    Affero General Public License for more details.
//
//    You should have received a copy of the GNU Affero General Public
//    License along with this library; if not, write to the Free Software
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
//
//    contact: José Miguel Rivero (rivero@cs.upc.edu)
//             Computer Science Department
//             Universitat Politecnica de Catalunya
//             despatx Omega.110 - Campus Nord UPC
//             08034 Barcelona.  SPAIN
//
//////////////////////////////////////////////////////////////////////

#include "CodeGenVisitor.h"
#include "antlr4-runtime.h"

#include "../common/TypesMgr.h"
#include "../common/SymTable.h"
#include "../common/TreeDecoration.h"
#include "../common/code.h"

#include <string>
#include <cstddef>    // std::size_t

// uncomment the following line to enable debugging messages with DEBUG*
//  #define DEBUG_BUILD
#include "../common/debug.h"

// using namespace std;


// Constructor
CodeGenVisitor::CodeGenVisitor(TypesMgr       & Types,
                               SymTable       & Symbols,
                               TreeDecoration & Decorations) :
  Types{Types},
  Symbols{Symbols},
  Decorations{Decorations} {
}

// Accessor/Mutator to the attribute currFunctionType
TypesMgr::TypeId CodeGenVisitor::getCurrentFunctionTy() const {
  return currFunctionType;
}

void CodeGenVisitor::setCurrentFunctionTy(TypesMgr::TypeId type) {
  currFunctionType = type;
}

// Methods to visit each kind of node:
//
antlrcpp::Any CodeGenVisitor::visitProgram(AslParser::ProgramContext *ctx) {
  DEBUG_ENTER();
  code my_code;
  SymTable::ScopeId sc = getScopeDecor(ctx);
  Symbols.pushThisScope(sc);
  for (auto ctxFunc : ctx->function()) { 
    subroutine subr = visit(ctxFunc);
    my_code.add_subroutine(subr);
  }
  Symbols.popScope();
  DEBUG_EXIT();
  return my_code;
}

antlrcpp::Any CodeGenVisitor::visitFunction(AslParser::FunctionContext *ctx) {
  DEBUG_ENTER();
  SymTable::ScopeId sc = getScopeDecor(ctx);
  Symbols.pushThisScope(sc);
  subroutine subr(ctx->ID()->getText());
  codeCounters.reset();

  if (ctx->basic_type()) {
    TypesMgr::TypeId t = getTypeDecor(ctx->basic_type());
    subr.add_param("_result", Types.to_string_basic(t), 1);
  }
  // Parameters
  visit(ctx->parameters());
  for (long unsigned int i = 0; i < ctx->parameters()->ID().size(); ++i) {
    TypesMgr::TypeId t = getTypeDecor(ctx->parameters()->type(i));
    std::string name = ctx->parameters()->ID(i)->getText(); 
    subr.add_param(name, Types.to_string_basic(t), 1);
  }

  // Declarations
  visit(ctx->declarations());
  ctx->declarations();
  for (long unsigned int i = 0; i < ctx->declarations()->variable_decl().size(); ++i) {
    TypesMgr::TypeId t = getTypeDecor(ctx->declarations()->variable_decl(i)->type());
    for (long unsigned int j = 0; j < ctx->declarations()->variable_decl(i)->ID().size(); ++j) {
      if (Types.isArrayTy(t)) {
        std::string name = ctx->declarations()->variable_decl(i)->ID(j)->getText();
        subr.add_var(name, Types.to_string_basic(t), Types.getSizeOfType(t));
      }
      else {
        std::string name = ctx->declarations()->variable_decl(i)->ID(j)->getText();
        subr.add_var(name, Types.to_string_basic(t), 1);
      }
    }
  }

  instructionList && code = visit(ctx->statements());

  if (not Types.isVoidTy(getTypeDecor(ctx))) {
    code = code || instruction(instruction::RETURN());
  }

  subr.set_instructions(code);
  Symbols.popScope();
  DEBUG_EXIT();
  return subr;
}

antlrcpp::Any CodeGenVisitor::visitDeclarations(AslParser::DeclarationsContext *ctx) {
  DEBUG_ENTER();
  std::vector<var> lvars;
  // for (auto & varDeclCtx : ctx->variable_decl()) {
  //   var onevar = visit(varDeclCtx);
  //   lvars.push_back(onevar);
  // }
  for (auto & varDeclCtx : ctx->variable_decl()) {
    std::vector<var> somevars = visit(varDeclCtx);
    for (auto & onevar : somevars) {
      lvars.push_back(onevar);
    }
  }
  /* EL PROFE LO TIENE ASI PARA LOS ARRAYS
  for (auto & varDeclCtx : ctx->variable_decl()) {
    std::vector<var> somevars = visit(varDeclCtx);
    for (auto & onevar : somevars) {
      lvars.push_back(onevar);
    }
  }
  */
  DEBUG_EXIT();
  return lvars;
}

antlrcpp::Any CodeGenVisitor::visitVariable_decl(AslParser::Variable_declContext *ctx) {
  DEBUG_ENTER();
  TypesMgr::TypeId   t1 = getTypeDecor(ctx->type());
  std::size_t size = Types.getSizeOfType(t1);
  std::vector<var> vars;

  //jp_chkt_02
  for (auto varDeclCtx : ctx->ID()) {
    vars.push_back(var{varDeclCtx->getText(), Types.to_string_basic(t1), size});
  }
  DEBUG_EXIT();
  return vars;
}

antlrcpp::Any CodeGenVisitor::visitStatements(AslParser::StatementsContext *ctx) {
  DEBUG_ENTER();
  instructionList code;
  int i = 0;
  for (auto stCtx : ctx->statement()) {
    ++i;
    
    instructionList && codeS = visit(stCtx);
    code = code || codeS;
    //std::cout << "Iteracio: " << i << " Name: " << stCtx->getText() << std::endl;
  }
  DEBUG_EXIT();
  return code;
}

antlrcpp::Any CodeGenVisitor::visitAssignStmt(AslParser::AssignStmtContext *ctx) {
  DEBUG_ENTER();
  instructionList code;
  CodeAttribs     && codAtsE1 = visit(ctx->left_expr());
  std::string           addr1 = codAtsE1.addr;
  instructionList &     code1 = codAtsE1.code;
  std::string          offs1 = codAtsE1.offs;
  TypesMgr::TypeId t1 = getTypeDecor(ctx->left_expr());

  CodeAttribs     && codAtsE2 = visit(ctx->expr());
  std::string           addr2 = codAtsE2.addr;
  instructionList &     code2 = codAtsE2.code;
  std::string          offs2 = codAtsE2.offs;
  TypesMgr::TypeId t2 = getTypeDecor(ctx->expr());

  code = code1 || code2;

  // float = int/bool
  if (Types.isFloatTy(t1) and not Types.isFloatTy(t2)) {
    std::string temp = "%"+codeCounters.newTEMP();
    code = code || instruction::FLOAT(temp, addr2);
    addr2 = temp;
  }
  // addr1[offs1] = addr2
  if (offs1.size() > 0) {
    code = code || instruction::XLOAD(addr1, offs1, addr2);
  }
  else {
    code = code || instruction::LOAD(addr1, addr2);
  }
  DEBUG_EXIT();
  return code;
}

antlrcpp::Any CodeGenVisitor::visitIfStmt(AslParser::IfStmtContext *ctx) {
  DEBUG_ENTER();
  instructionList code;
  CodeAttribs     && codAtsE = visit(ctx->expr());
  std::string          addr1 = codAtsE.addr;
  instructionList &    code1 = codAtsE.code;
  instructionList &&   code2 = visit(ctx->statements(0)); //jp_chkt_03

  std::string label = codeCounters.newLabelIF();
  std::string labelEndIf = "endif"+label;
  code = code1 || instruction::FJUMP(addr1, labelEndIf) ||
         code2 || instruction::LABEL(labelEndIf);
  DEBUG_EXIT();
  return code;
}

antlrcpp::Any CodeGenVisitor::visitWhileStmt(AslParser::WhileStmtContext *ctx) {
  DEBUG_ENTER();
  instructionList code;
  CodeAttribs     && codAtsE = visit(ctx->expr());
  std::string          addr1 = codAtsE.addr;
  instructionList &    code1 = codAtsE.code;
  instructionList &&   code2 = visit(ctx->statements());

  std::string label = codeCounters.newLabelWHILE();
  
  std::string labelStartWhile = "startwhile"+label;
  std::string labelEndWhile = "endwhile"+label;
  
  code = instruction::LABEL(labelStartWhile) ||
         code1 || // evaluamos la condicion
         instruction::FJUMP(addr1, labelEndWhile) || // si es falsa salta al final
         code2 || // ejecutamos el codigo
         instruction::UJUMP(labelStartWhile) || // vuelve a evaluar la condicion
         instruction::LABEL(labelEndWhile);
  DEBUG_EXIT();
  return code;
}

antlrcpp::Any CodeGenVisitor::visitProcCall(AslParser::ProcCallContext *ctx) {
  //HA DE SER VOID
  //PROCEDURE CALL
  DEBUG_ENTER();
  TypesMgr::TypeId  t1 = getTypeDecor(ctx->ident());
  auto typesParams = Types.getFuncParamsTypes(t1);

  instructionList code;
  instructionList lpush;
  instructionList lpop;

  for (size_t i = 0; i < ctx->expr().size(); ++i){
    CodeAttribs     &&  codAtsE = visit(ctx->expr(i));
    std::string         addr1 = codAtsE.addr;
    instructionList &   code1 = codAtsE.code;
    
    code = code || code1;
    std::string temp = addr1;

    TypesMgr::TypeId t2 = getTypeDecor(ctx->expr(i));

    if (Types.isFloatTy(typesParams[i]) and Types.isIntegerTy(t2)){
      temp = "%"+codeCounters.newTEMP();
      code = code || instruction::FLOAT(temp, addr1);
    }

    if (Types.isArrayTy(typesParams[i])) {
      temp = "%"+codeCounters.newTEMP();
      code = code || instruction::ALOAD(temp, addr1);
    }
    
    lpush = lpush || instruction::PUSH(temp); 
    lpop = lpop || instruction::POP(); 
  }

  if (not Types.isVoidFunction(t1)) {
    lpush = instruction::PUSH() || lpush;
    lpop = lpop || instruction::POP();
  }

  code = code || lpush;

  std::string name = ctx->ident()->getText();
  code = code || instruction::CALL(name);

  code = code || lpop;
  DEBUG_EXIT();
  return code;
}

antlrcpp::Any CodeGenVisitor::visitReadStmt(AslParser::ReadStmtContext *ctx) {
  DEBUG_ENTER();
  CodeAttribs     && codAtsE = visit(ctx->left_expr());
  std::string          addr1 = codAtsE.addr;
  std::string          offs1 = codAtsE.offs;
  instructionList &    code1 = codAtsE.code;
  instructionList &     code = code1;
  TypesMgr::TypeId t1 = getTypeDecor(ctx->left_expr());

  std::string temp = "%"+codeCounters.newTEMP();

  if (Types.isCharacterTy(t1))
    code = code || instruction::READC(temp);
  else if (Types.isFloatTy(t1))
    code = code || instruction::READF(temp);
  else //int o bool
    code = code || instruction::READI(temp);

  if (offs1.size() > 0) {
    // addr1[offs1] = temp
    code = code || instruction::XLOAD(addr1, offs1, temp);
  }
  else {
    code = code || instruction::LOAD(addr1, temp);
  }

  DEBUG_EXIT();
  return code;
}

antlrcpp::Any CodeGenVisitor::visitWriteExpr(AslParser::WriteExprContext *ctx) {
  DEBUG_ENTER();
  CodeAttribs     && codAt1 = visit(ctx->expr());
  // std::string         offs1 = codAt1.offs;
  std::string      addr = codAt1.addr;
  instructionList &    code1 = codAt1.code;
  instructionList &     code = code1;
  TypesMgr::TypeId t1 = getTypeDecor(ctx->expr());

  if (Types.isIntegerTy(t1) || Types.isBooleanTy(t1))
    code = code || instruction::WRITEI(addr);
  else if (Types.isFloatTy(t1))
    code = code || instruction::WRITEF(addr);

  DEBUG_EXIT();
  return code;
}

antlrcpp::Any CodeGenVisitor::visitWriteString(AslParser::WriteStringContext *ctx) {
  DEBUG_ENTER();
  instructionList code;
  std::string s = ctx->STRING()->getText();
  code = code || instruction::WRITES(s);
  DEBUG_EXIT();
  return code;
}

antlrcpp::Any CodeGenVisitor::visitRetStmt(AslParser::RetStmtContext *ctx) {
  DEBUG_ENTER();
  instructionList code;
  if (ctx->expr()) {
    CodeAttribs     && codAtExpr = visit(ctx->expr());
    std::string         addrExpr = codAtExpr.addr;
    instructionList &   codeExpr = codAtExpr.code;

    code = codeExpr || instruction::LOAD("_result",addrExpr) || instruction::RETURN();
  }
  DEBUG_EXIT();
  return code;
}

antlrcpp::Any CodeGenVisitor::visitLarray(AslParser::LarrayContext *ctx) {
  DEBUG_ENTER();
  CodeAttribs     && codAt1 = visit(ctx->ident());
  std::string         addr1 = codAt1.addr;
  instructionList &   code1 = codAt1.code;

  CodeAttribs     && codAt2 = visit(ctx->expr());
  std::string         addr2 = codAt2.addr;
  instructionList &   code2 = codAt2.code;

  instructionList && code = code1 || code2;


  if (Symbols.isParameterClass(ctx->ident()->getText())) {
    std::string temp = "%"+codeCounters.newTEMP();
    code = code || instruction::LOAD(temp, addr1);
    addr1 = temp;
  }

  CodeAttribs codAts(addr1, addr2, code); 
  DEBUG_EXIT();
  return codAts;
}

antlrcpp::Any CodeGenVisitor::visitLexprIdent(AslParser::LexprIdentContext *ctx) {
  DEBUG_ENTER();
  CodeAttribs && codAts = visit(ctx->ident());
  DEBUG_EXIT();
  return codAts;
}

antlrcpp::Any CodeGenVisitor::visitParent(AslParser::ParentContext *ctx) {
  DEBUG_ENTER();
  CodeAttribs codAts = visit(ctx->expr());
  DEBUG_EXIT();
  return codAts;
}

antlrcpp::Any CodeGenVisitor::visitFunc(AslParser::FuncContext *ctx) {
  // NO PUEDE SER VOID
  DEBUG_ENTER();
  TypesMgr::TypeId  t1 = getTypeDecor(ctx->ident());
  auto typesParams = Types.getFuncParamsTypes(t1);
  instructionList code;
  instructionList lpush;
  instructionList lpop;

  for (size_t i = 0; i < ctx->expr().size(); ++i){
    CodeAttribs     &&  codAtsE = visit(ctx->expr(i));
    std::string         addr1 = codAtsE.addr;
    instructionList &   code1 = codAtsE.code;

    code = code || code1;
    std::string temp = addr1;
    TypesMgr::TypeId t2 = getTypeDecor(ctx->expr(i));

    if (Types.isFloatTy(typesParams[i]) and Types.isIntegerTy(t2)){
      temp = "%"+codeCounters.newTEMP();
      code = code || instruction::FLOAT(temp, addr1);
    }
    
    lpush = lpush || instruction::PUSH(temp); 
    lpop = lpop || instruction::POP(); 
  }

  code = code || instruction::PUSH() || lpush;

  std::string name = ctx->ident()->getText();
  code = code || instruction::CALL(name);

  std::string temp2 = "%"+codeCounters.newTEMP();  // get the return value
  code = code || lpop || instruction::POP(temp2);

  CodeAttribs codAts(temp2, "", code);

  DEBUG_EXIT();
  return codAts;
}

antlrcpp::Any CodeGenVisitor::visitMinus_unari(AslParser::Minus_unariContext *ctx) {
    DEBUG_ENTER();
  CodeAttribs     && codAt1 = visit(ctx->expr());
  std::string         addr1 = codAt1.addr;
  instructionList &   code = codAt1.code;
  //instructionList &&   code = code1;
  TypesMgr::TypeId t1 = getTypeDecor(ctx->expr());

  std::string temp = "%"+codeCounters.newTEMP();

  if (Types.isFloatTy(t1)) {
    code = code || instruction::FNEG(temp, addr1);
  }
  else {
    code = code || instruction::NEG(temp, addr1);
  }
  
  CodeAttribs codAts(temp, "", code);
  DEBUG_EXIT();
  return codAts;
}

antlrcpp::Any CodeGenVisitor::visitArithmetic(AslParser::ArithmeticContext *ctx) {
  DEBUG_ENTER();
  CodeAttribs     && codAt1 = visit(ctx->expr(0));
  std::string         addr1 = codAt1.addr;            //Address
  instructionList &   code1 = codAt1.code;            //Instruction list
  CodeAttribs     && codAt2 = visit(ctx->expr(1));
  std::string         addr2 = codAt2.addr;
  instructionList &   code2 = codAt2.code;
  instructionList &&   code = code1 || code2;

  TypesMgr::TypeId t1 = getTypeDecor(ctx->expr(0));
  TypesMgr::TypeId t2 = getTypeDecor(ctx->expr(1));
  TypesMgr::TypeId  t = getTypeDecor(ctx);

  std::string temp = "%"+codeCounters.newTEMP();
  
  if (Types.isIntegerTy(t)) {
    if (ctx->MUL())
      code = code || instruction::MUL(temp, addr1, addr2); // Amb floats es FMUL
    else if (ctx->PLUS())
      code = code || instruction::ADD(temp, addr1, addr2); // Amb floats es FADD
    else if (ctx->MINUS())  
      code = code || instruction::SUB(temp, addr1, addr2); // Amb floats es FSUB
    else if (ctx->DIV())
      code = code || instruction::DIV(temp, addr1, addr2); // Amb floats es FDIV
  }
  else {
    if (Types.isIntegerTy(t1)){
      std::string temp1 = "%"+codeCounters.newTEMP();
      code = code || instruction::FLOAT(temp1, addr1);
      addr1 = temp1;
    }

    else if (Types.isIntegerTy(t2)){
      std::string temp2 = "%"+codeCounters.newTEMP();
      code = code || instruction::FLOAT(temp2, addr2);
      addr2 = temp2;
    }

    if (ctx->MUL())
      code = code || instruction::FMUL(temp, addr1, addr2);
    else if (ctx->PLUS())
      code = code || instruction::FADD(temp, addr1, addr2);
    else if (ctx->MINUS())  
      code = code || instruction::FSUB(temp, addr1, addr2);
    else if (ctx->DIV())
      code = code || instruction::FDIV(temp, addr1, addr2);
  }
  CodeAttribs codAts(temp, "", code);
  DEBUG_EXIT();
  return codAts;
}

antlrcpp::Any CodeGenVisitor::visitRelational(AslParser::RelationalContext *ctx) {
  DEBUG_ENTER();
  CodeAttribs     && codAt1 = visit(ctx->expr(0));
  std::string         addr1 = codAt1.addr;
  instructionList &   code1 = codAt1.code;
  CodeAttribs     && codAt2 = visit(ctx->expr(1));
  std::string         addr2 = codAt2.addr;
  instructionList &   code2 = codAt2.code;
  instructionList &&   code = code1 || code2;
  TypesMgr::TypeId t1 = getTypeDecor(ctx->expr(0));
  TypesMgr::TypeId t2 = getTypeDecor(ctx->expr(1));
  // TypesMgr::TypeId  t = getTypeDecor(ctx);
  std::string temp = "%"+codeCounters.newTEMP();

  // los 2 no son float
  if (not Types.isFloatTy(t1) and not Types.isFloatTy(t2)) {
    if (ctx->LT()) {
      code = code || instruction::LT(temp, addr1, addr2);
    }
    else if (ctx->LE()) {
      code = code || instruction::LE(temp, addr1, addr2);
    }
    else if (ctx->EQUAL()) {
      code = code || instruction::EQ(temp, addr1, addr2);
    }
    else if (ctx->NEQ()) {
      code = code || instruction::EQ(temp, addr1, addr2) || instruction::NOT(temp, temp);
    }
    else if (ctx->GT()) {
      code = code || instruction::LE(temp, addr1, addr2) || instruction::NOT(temp, temp);
    }
    else if (ctx->GE()) {
      code = code || instruction::LT(temp, addr1, addr2) || instruction::NOT(temp, temp);
    }
  }

  else {
    std::string temp1 = addr1;
    std::string temp2 = addr2;
    if (Types.isIntegerTy(t1)) {
      temp1 = "%"+codeCounters.newTEMP();
      code = code || instruction::FLOAT(temp1, addr1);
    }
    if (Types.isIntegerTy(t2)) {
      temp2 = "%"+codeCounters.newTEMP();
      code = code || instruction::FLOAT(temp2, addr2);
    }

    if (ctx->LT()) {
      code = code || instruction::FLT(temp, temp1, temp2);
    }
    else if (ctx->LE()) {
      code = code || instruction::FLE(temp, temp1, temp2);
    }
    else if (ctx->EQUAL()) {
      code = code || instruction::FEQ(temp, temp1, temp2);
    }
    else if (ctx->NEQ()) {
      code = code || instruction::FEQ(temp, temp1, temp2) || instruction::NOT(temp, temp);
    }
    else if (ctx->GT()) {
      code = code || instruction::FLE(temp, temp1, temp2) || instruction::NOT(temp, temp);
    }
    else if (ctx->GE()) {
      code = code || instruction::FLT(temp, temp1, temp2) || instruction::NOT(temp, temp);
    }
  }
  
  CodeAttribs codAts(temp, "", code);
  DEBUG_EXIT();
  return codAts;
}

antlrcpp::Any CodeGenVisitor::visitLogical_unari(AslParser::Logical_unariContext *ctx) {
    DEBUG_ENTER();
  CodeAttribs     && codAt1 = visit(ctx->expr());
  std::string         addr1 = codAt1.addr;
  instructionList &   code = codAt1.code;
  //instructionList &&   code = code1;
  // TypesMgr::TypeId t1 = getTypeDecor(ctx->expr(0));
  // TypesMgr::TypeId t2 = getTypeDecor(ctx->expr(1));
  // TypesMgr::TypeId  t = getTypeDecor(ctx);

  std::string temp = "%"+codeCounters.newTEMP();

  if (ctx->NOT())
    code = code || instruction::NOT(temp, addr1);
  
  CodeAttribs codAts(temp, "", code);
  DEBUG_EXIT();
  return codAts;
}

antlrcpp::Any CodeGenVisitor::visitLogical(AslParser::LogicalContext *ctx) {
    DEBUG_ENTER();
  CodeAttribs     && codAt1 = visit(ctx->expr(0));
  std::string         addr1 = codAt1.addr;
  instructionList &   code1 = codAt1.code;
  CodeAttribs     && codAt2 = visit(ctx->expr(1));
  std::string         addr2 = codAt2.addr;
  instructionList &   code2 = codAt2.code;
  instructionList &&   code = code1 || code2;
  // TypesMgr::TypeId t1 = getTypeDecor(ctx->expr(0));
  // TypesMgr::TypeId t2 = getTypeDecor(ctx->expr(1));
  // TypesMgr::TypeId  t = getTypeDecor(ctx);

  std::string temp = "%"+codeCounters.newTEMP();

  if (ctx->AND()) {
    code = code || instruction::AND(temp, addr1, addr2);
  }
  else if (ctx->OR()) {
    code = code || instruction::OR(temp, addr1, addr2);
  }
  
  CodeAttribs codAts(temp, "", code);
  DEBUG_EXIT();
  return codAts;
}

antlrcpp::Any CodeGenVisitor::visitValue(AslParser::ValueContext *ctx) {
  DEBUG_ENTER();
  instructionList code;
  std::string temp = "%"+codeCounters.newTEMP();
  
  if (ctx->INTVAL())
    code = instruction::ILOAD(temp, ctx->getText());
  else if (ctx->FLOATVAL())
    code = instruction::FLOAD(temp, ctx->getText());
  else if (ctx->CHARVAL()) 
    code = instruction::CHLOAD(temp, ctx->getText());
  else if (ctx->FALSE())
    code = instruction::ILOAD(temp, "0");
  else if (ctx->TRUE())
    code = instruction::ILOAD(temp, "1");
    
  CodeAttribs codAts(temp, "", code);
  DEBUG_EXIT();
  return codAts;
}

antlrcpp::Any CodeGenVisitor::visitArray(AslParser::ArrayContext *ctx) {
  DEBUG_ENTER();

  CodeAttribs     && codAt1 = visit(ctx->ident());
  std::string         addr1 = codAt1.addr;
  instructionList &   code1 = codAt1.code;

  CodeAttribs     && codAt2 = visit(ctx->expr());
  std::string         addr2 = codAt2.addr;
  instructionList &   code2 = codAt2.code;

  instructionList && code = code1 || code2;

  std::string temp = "%"+codeCounters.newTEMP();

  if (Symbols.isParameterClass(ctx->ident()->getText())) {
    std::string temp1 = "%"+codeCounters.newTEMP();
    code = code || instruction::LOAD(temp1, addr1);
    addr1 = temp1;
  }
  code = code || instruction::LOADX(temp, addr1, addr2);

  CodeAttribs codAts(temp, "", code);


  DEBUG_EXIT();
  return codAts;
}

antlrcpp::Any CodeGenVisitor::visitExprIdent(AslParser::ExprIdentContext *ctx) {
  DEBUG_ENTER();
  CodeAttribs && codAts = visit(ctx->ident());
  DEBUG_EXIT();
  return codAts;
}

antlrcpp::Any CodeGenVisitor::visitIdent(AslParser::IdentContext *ctx) {
  DEBUG_ENTER();
  CodeAttribs codAts(ctx->ID()->getText(), "", instructionList());
  DEBUG_EXIT();
  return codAts;
}


// Getters for the necessary tree node atributes:
//   Scope and Type
SymTable::ScopeId CodeGenVisitor::getScopeDecor(antlr4::ParserRuleContext *ctx) const {
  return Decorations.getScope(ctx);
}
TypesMgr::TypeId CodeGenVisitor::getTypeDecor(antlr4::ParserRuleContext *ctx) const {
  return Decorations.getType(ctx);
}


// Constructors of the class CodeAttribs:
//
CodeGenVisitor::CodeAttribs::CodeAttribs(const std::string & addr,
                                         const std::string & offs,
                                         instructionList & code) :
  addr{addr}, offs{offs}, code{code} {
}

CodeGenVisitor::CodeAttribs::CodeAttribs(const std::string & addr,
                                         const std::string & offs,
                                         instructionList && code) :
  addr{addr}, offs{offs}, code{code} {
}
