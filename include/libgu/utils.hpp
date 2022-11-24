#ifndef LIBGU_UTILS_H
#define LIBGU_UTILS_H

#include <sstream>

#include "types.hpp"

namespace libgu {

template<FromStr T>
T cast(const String& str) { // WARNING: no type checking
  T res;
  std::istringstream ss(str);
  ss >> res;
  return res;
}

template<>
String cast(const String& str) {
  return str;
}

} // end namespace libgu

#endif // end header guard
