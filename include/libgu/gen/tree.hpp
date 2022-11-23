#ifndef LIBGU_TREE_H
#define LIBGU_TREE_H

#include <vector>
#include <functional>

#include "rand.hpp"

namespace libgu {

template<typename _Weight>
class TreeFormatter {
private:
  std::function<String(int, int, _Weight)> _fmt;

public:
  // TODO
};

template<typename _Weight>
class Tree {
private:
  int _size;
  std::vector<std::vector<std::pair<int, _Weight>>> _edges;

public:
  // TODO

  String format(const TreeFormatter& fmt) {
    std::stringstream ss;
    ss << _size << ' ' << (_size - 1) << '\n';
  }
};

namespace rand {

template<typename _Weight = int>
inline Tree<_Weight> tree(int siz) {
  std::vector<int> prufer(siz - 2);
  for (int& item : prufer)
    item = integer(1, siz);

  std::vector<int> degree(siz + 1, 1);
  for (int item : prufer)
    ++ degree[item];

  int ptr = 1;
  while (degree[ptr] != 1)
    ++ ptr;
  int leaf = ptr;

  for (int item : prufer) {
    degree[item] -= 1;
    while (degree[ptr] != 1)
      ++ ptr;
    degree[ptr] -= 1;
    leaf = ptr;
  }
}

} // end namespace

} // end namespace

#endif // end header guard
