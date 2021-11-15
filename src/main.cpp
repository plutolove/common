#include <iostream>

#include "common/error_codes.h"
#include "common/type_cast.h"

using namespace common;
using namespace ErrorCode;
int main() {
  std::cout << ErrorCodeStr<0> << std::endl;
  std::cout << OK << std::endl;
  return 0;
}
