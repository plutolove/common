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
  std::set<int> s;
  auto* func = reinterpret_cast<void (*)(std::set<int>*)>(
      res.function_name_to_symbol["_Z8set_testPSt3setIiSt4lessIiESaIiEE"]);
  func(&s);
  for (auto& v : s) {
    std::cout << v << std::endl;
  }
  return 0;
}
