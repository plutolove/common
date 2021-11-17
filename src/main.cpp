#include <iostream>

#include "common/error_codes.h"
#include "common/type_cast.h"
#include "common/type_promation.h"

using namespace common;
using namespace ErrorCode;

class T : TypePromation<T> {};

int main() {
  std::cout << ErrorCodeStr<0> << std::endl;
  std::cout << OK << std::endl;
  return 0;
}
