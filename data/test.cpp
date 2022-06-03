#include <string>
extern int run_lib();
int mmmax() { return 2 + run_lib(); }
int test_string(std::string* val) {
  *val = "345546rdtfdfg345fgthd";
  return 2 + run_lib();
}