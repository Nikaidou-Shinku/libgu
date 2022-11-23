#include "libgu/io.hpp"
#include "libgu/gen/rand.hpp"

#include <fstream>

using namespace libgu;

int main() {
  int len;
  std::cin >> len;

  std::ofstream fout("perm.in");
  fout << rand::permutation(len) << std::endl;
  return 0;
}
