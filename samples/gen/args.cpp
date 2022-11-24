#include "libgu/args.hpp"
#include "libgu/utils.hpp"
#include "libgu/gen/tree.hpp"

using namespace libgu;

int main(int argc, char *argv[]) {
  Args args(argc, argv);

  int n = args.get<int>("maxn");
  Tree t = rand::tree(n);

  if (args.get("weighted") == "true") {
    std::cout << t.format<Weighted<int>>();
  } else {
    std::cout << t.format();
  }
  return 0;
}
