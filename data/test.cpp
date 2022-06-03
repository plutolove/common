#include <set>
#include <string>

extern int run_lib();

int mmmax() { return 2 + run_lib(); }

int test_string(std::string* val) {
  *val = "345546rdtfdfg345fgthd";
  return 2 + run_lib();
}

void set_test(std::set<int>* s) {
  for (size_t i = 0; i < 10; i++) s->insert(i);
}