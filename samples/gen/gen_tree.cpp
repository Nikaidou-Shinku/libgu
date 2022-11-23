#include "libgu/gen/tree.hpp"

using namespace libgu;

constexpr int N = 15;

int main() {
  rand::set_seed(114514);

  auto weight_gen = [](int le, int re) {
    return rand::integer(le - N, re + N);
  };

  Tree t = rand::tree<int>(N, weight_gen);

  std::cout << t.format<Weighted<int>>();
  return 0;
}
