#ifndef LIBGU_RAND_H
#define LIBGU_RAND_H

#include <vector>
#include <random>
#include <concepts>

#include "../types.hpp"

namespace libgu {

namespace charset {

inline const String numeric = "0123456789";
inline const String alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
inline const String loweralpha = "abcdefghijklmnopqrstuvwxyz";
inline const String symbol = "!@#$%^&*()-_+=";
inline const String symbol_extra = "~`[]{}|\\:;\"'<>,.?/";

} // end namespace charset

namespace rand {

namespace _details {

static std::default_random_engine e;

} // end namespace _details

inline void set_seed(std::default_random_engine::result_type v) {
  _details::e.seed(v);
}

template<std::integral T>
inline T integer(T l, T r) {
  std::uniform_int_distribution<T> d(l, r);
  return d(_details::e);
}

template<std::floating_point T>
inline T real(T l, T r) {
  std::uniform_real_distribution<T> d(l, r);
  return d(_details::e);
}

inline auto string(
  std::size_t len,
  const String& alphabet = charset::loweralpha
) -> String {
  String res;
  std::size_t siz = alphabet.length();

  while (len --) {
    std::size_t pos = integer(static_cast<std::size_t>(0), siz - 1);
    char c = alphabet[pos];
    res.push_back(c);
  }

  return res;
}

template<std::integral T>
inline std::vector<T> permutation(T len) {
  std::vector<T> res(len);
  for (T i = 0; i < len; ++ i)
    res[i] = i + 1;

  for (T i = 0; i < len; ++ i) {
    T pos = integer(0, i);
    std::swap(res[pos], res[i]);
  }

  return res;
}

} // end namespace rand

} // end namespace libgu

#endif // end header guard
