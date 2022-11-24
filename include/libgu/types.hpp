#ifndef LIBGU_TYPES_H
#define LIBGU_TYPES_H

#include <iostream>
#include <string>

namespace libgu {

using f64 = double;
using String = std::string;

template<typename T>
concept FromStr =
  requires(std::istream& in, T t) {
    in >> t;
  };

template<typename T>
concept Display =
  requires(std::ostream& out, T t) {
    out << t;
  };

} // end namespace libgu

#endif // end header guard
