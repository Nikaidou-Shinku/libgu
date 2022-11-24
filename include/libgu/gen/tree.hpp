#ifndef LIBGU_TREE_H
#define LIBGU_TREE_H

#include <sstream>
#include <vector>
#include <functional>
#include <concepts>

#include "rand.hpp"

namespace libgu {

template<typename _Weight>
using Edge = std::tuple<int, int, _Weight>;

template<Display _Weight>
class Weighted {
public:
  static String format_edge(const Edge<_Weight>& e) {
    auto [le, re, w] = e;
    std::ostringstream ss;
    ss << le << ' ' << re << ' ' << w;
    return ss.str();
  }
};

template<typename _Weight>
class Unweighted {
public:
  static String format_edge(const Edge<_Weight>& e) {
    auto [le, re, _w] = e;
    std::ostringstream ss;
    ss << le << ' ' << re;
    return ss.str();
  }
};

// TODO: design shuffle APIs

// namespace shuffle {

// template<typename T>
// using ShuffleFunc = std::function<void(std::vector<T>&)>;

// template<typename T>
// void none(std::vector<T>&) { }

// template<typename _Weight>
// void random(std::vector<Edge<_Weight>>& edges) {
//   std::size_t siz = edges.size();
//   for (std::size_t i = 0; i < siz; ++ i) {
//     std::size_t pos = rand::integer(static_cast<std::size_t>(0), i);
//     std::swap(edges[pos], edges[i]);
//   }
//   for (std::size_t i = 0; i < siz; ++ i) {
//     if (rand::integer(0, 1) == 1) {
//       std::swap(edges[i].0, edges[i].1);
//     }
//   }
// }

// } // end namespace shuffle

template<typename _Weight>
class Tree {
private:
  int _size;
  std::vector<std::vector<std::pair<int, _Weight>>> _edges;

public:
  // WARNING: Please try not to use this function
  Tree(int siz = 1): _size(siz), _edges(siz + 1) { }

  // WARNING: Please try not to use this function
  void link(int u, int v, const _Weight& w) {
    _edges[u].emplace_back(v, w);
    _edges[v].emplace_back(u, w);
  }

  template<typename F = Unweighted<_Weight>>
  requires requires(const Edge<_Weight>& e) {
    { F::format_edge(e) } -> std::same_as<String>;
  }
  auto format(
    // TODO: pass shuffle func as param
  ) -> String const {
    std::vector<Edge<_Weight>> edge_list;
    for (int i = 1; i <= _size; ++ i) {
      for (auto [j, w] : _edges[i]) {
        if (i < j) {
          edge_list.emplace_back(i, j, w);
        }
      }
    }

    // TODO: shuffle here
    // shuffle_func(edges_str);

    std::ostringstream ss;
    ss << _size << ' ' << (_size - 1) << '\n';
    for (const auto& item : edge_list)
      ss << F::format_edge(item) << '\n';
    return ss.str();
  }
};

namespace rand {

template<typename _Weight>
using WeightGen = std::function<_Weight(int, int)>;

template<typename _Weight = int>
inline auto tree(
  int siz,
  WeightGen<_Weight> w_gen = [](int, int) { return 1; }
) -> Tree<_Weight> {
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

  Tree<_Weight> res(siz);
  for (int item : prufer) {
    res.link(leaf, item, w_gen(leaf, item));
    -- degree[item];
    if (degree[item] == 1 && item < ptr)
      leaf = item;
    else {
      ++ ptr;
      while (degree[ptr] != 1)
        ++ ptr;
      leaf = ptr;
    }
  }
  res.link(leaf, siz, w_gen(leaf, siz));
  return res;
}

} // end namespace

} // end namespace

#endif // end header guard
