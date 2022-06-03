#include <iostream>
extern int run_lib();
int mmmax() {
  std::cout << "--------------- run test" << std::endl;
  return 2 + run_lib();
}