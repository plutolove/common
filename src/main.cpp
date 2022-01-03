#include <iostream>

#include "clang/CodeGen/CodeGenAction.h"
#include "clang/Driver/Action.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/TextDiagnosticPrinter.h"
#include "common/cow.h"
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
  compile("/home/meng/CLionProjects/common/src/test.cpp");
  return 0;
}
