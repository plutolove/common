#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>

#include <iostream>

#include "clang/CodeGen/CodeGenAction.h"
#include "clang/Driver/Action.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/TextDiagnosticPrinter.h"
#include "common/error_codes.h"
#include "common/type_cast.h"
#include "common/type_promation.h"
#include "jit/sql_jit.h"

using namespace common;
using namespace ErrorCode;

llvm::Module* compile(const char* filename) {
  clang::CompilerInstance compiler;
  auto invocation = std::make_shared<clang::CompilerInvocation>();
  llvm::IntrusiveRefCntPtr<clang::DiagnosticIDs> DiagID(
      new clang::DiagnosticIDs());
  auto diagOptions = new clang::DiagnosticOptions();
  clang::DiagnosticsEngine Diags(
      DiagID, diagOptions,
      new clang::TextDiagnosticPrinter(llvm::errs(), diagOptions));
  std::vector<const char*> arguments = {filename};
  clang::CompilerInvocation::CreateFromArgs(*invocation, arguments, Diags);

  compiler.setInvocation(invocation);
  compiler.setDiagnostics(new clang::DiagnosticsEngine(
      DiagID, diagOptions,
      new clang::TextDiagnosticPrinter(llvm::errs(), diagOptions)));
  std::unique_ptr<clang::CodeGenAction> action(new clang::EmitLLVMOnlyAction());
  compiler.ExecuteAction(*action);
  std::unique_ptr<llvm::Module> result = action->takeModule();
  llvm::errs() << *result;
  return result.release();
}

int main() {
  // sql::SQLJit jit;
  // std::cout << ErrorCodeStr<0> << std::endl;
  // std::cout << OK << std::endl;
  /*
  [](llvm::Module& module) {
            auto& context = module.getContext();
            llvm::IRBuilder<> b(context);

            auto* func_declaration_type =
                llvm::FunctionType::get(b.getVoidTy(), {}, false);
  auto* func_declaration = llvm::Function::Create(
      func_declaration_type, llvm::Function::ExternalLinkage, "test_function",
      module);

  auto* value_type = b.getInt64Ty();
  auto* pointer_type = value_type->getPointerTo();

  auto* func_type = llvm::FunctionType::get(b.getVoidTy(), {pointer_type},
                                            false);
  auto* function = llvm::Function::Create(
      func_type, llvm::Function::ExternalLinkage, "test_name", module);
  auto* entry = llvm::BasicBlock::Create(context, "entry", function);

  auto* argument = function->args().begin();
  b.SetInsertPoint(entry);

  b.CreateCall(func_declaration);

  auto* load_argument = b.CreateLoad(value_type, argument);
  auto* value = b.CreateAdd(load_argument, load_argument);
  b.CreateRet(value);
}
*/
  sql::SQLJit::CompiledModule res =
      sql::SQLJit::getInstance().compileWithExtraIR(
          "/home/meng/CLionProjects/common/data/test.ll",
          [](llvm::Module& module) {
            auto& context = module.getContext();
            llvm::IRBuilder<> b(context);

            auto* func_declaration_type =
                llvm::FunctionType::get(b.getInt32Ty(), {}, false);
            auto func_declaration =
                module.getOrInsertFunction("_Z5mmmaxv", func_declaration_type);
            /* llvm::Function::Create(
                func_declaration_type, llvm::Function::ExternalLinkage,
                "_Z5mmmaxv", module); */

            auto* value_type = b.getInt64Ty();
            auto* pointer_type = value_type->getPointerTo();

            auto* func_type =
                llvm::FunctionType::get(b.getInt32Ty(), {}, false);
            auto* function = llvm::Function::Create(
                func_type, llvm::Function::ExternalLinkage, "test_name",
                module);
            auto* entry = llvm::BasicBlock::Create(context, "entry", function);

            auto* argument = function->args().begin();
            b.SetInsertPoint(entry);

            auto value = b.CreateCall(func_declaration);
            b.CreateRet(value);
          });

  for (auto& kv : res.function_name_to_symbol) {
    if (kv.first != "test_name") continue;
    std::cout << "name: " << kv.first << "\t addr: " << kv.second << std::endl;
    auto* func = reinterpret_cast<int (*)()>(kv.second);
    // std::string val = "x";
    std::cout << "res: " << func() << std::endl;
    // std::cout << val << std::endl;
  }
  return 0;
}
