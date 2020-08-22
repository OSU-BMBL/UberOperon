#include "../rbh/my_rbh.h"

template<typename GeneType>
void RunMe(const char* file) {
  MyRbh rbh(file);
  rbh.Update();
  rbh.Output();
}

int main(int /*argc*/, char** /*argv[]*/) {
  RunMe<std::string>("../../data_test/NC_000853.out");
  return 0;
}
