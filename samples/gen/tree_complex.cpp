#include "libgu/gen/tree.hpp"

#include <sstream>

using namespace libgu;

constexpr int N = 15;

struct Weight { int a; double b; };

class TreeFormatter {
public:
  static String format_edge(const Edge<Weight>& e) {
    auto [le, re, w] = e;
    std::stringstream ss;
    ss << le << " --(" << std::fixed << w.b << ", " << w.a << ")--> " << re;
    return ss.str();
  }
};

int main() {
  rand::set_seed(114514);

  auto weight_gen = [](int le, int re) {
    Weight w;
    w.a = rand::integer(le - N, re + N);
    w.b = rand::real(100.0, 200.0);
    return w;
  };

  Tree t = rand::tree<Weight>(N, weight_gen);

  std::cout << t.format<TreeFormatter>();
  return 0;
}
