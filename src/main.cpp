#include <iostream>

#include "common/cow.h"
#include "common/error_codes.h"
#include "common/type_cast.h"
#include "common/type_promation.h"
#include "jit/sql_jit.h"

using namespace common;
using namespace ErrorCode;

class T : TypePromation<T> {};
class TT : COW<T> {};

int main() {
  sql::SQLJit jit;
  std::cout << ErrorCodeStr<0> << std::endl;
  std::cout << OK << std::endl;
  return 0;
}
