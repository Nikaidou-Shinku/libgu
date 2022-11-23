#ifndef LIBGU_IO_H
#define LIBGU_IO_H

#include <iostream>
#include <vector>

#include "types.hpp"

namespace libgu {

template<Display T>
auto operator << (
  std::ostream& out,
  const std::vector<T>& rhs
) -> std::ostream& {
  size_t len = rhs.size();
  for (size_t i = 0; i < len; ++ i) {
    out << rhs[i];
    if (i + 1 != len)
      out << ' ';
  }
  return out;
}

} // end namespace libgu

#endif // end header guard
