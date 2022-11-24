#ifndef LIBGU_ARGS_H
#define LIBGU_ARGS_H

#include <cstdlib>
#include <vector>
#include <map>

#include "types.hpp"
#include "utils.hpp"

namespace libgu {

class Args {
private:
  std::map<String, String> args;

public:
  Args(int argc, char *argv[]) {
    std::vector<String> arg_list;
    for (int i = 1; i < argc; ++ i)
      arg_list.emplace_back(argv[i]);

    std::size_t siz = arg_list.size();
    for (std::size_t i = 0; i < siz; ++ i) {
      String& arg = arg_list[i];
      if (arg.starts_with("--")) {
        String key = arg.substr(2);
        String value = "true";

        if (i + 1 < siz) {
          String& nxt = arg_list[i + 1];
          if (!nxt.starts_with("--"))
            value = nxt;
        }

        args[key] = value;
      }
    }
  }

  template<FromStr T = String>
  T get(const String& key) const { // WARNING: no type checking
    if (args.contains(key)) {
      String raw = args.at(key);
      return cast<T>(raw);
    } else {
      if constexpr (std::is_same_v<T, String>) {
        return "false";
      } else {
        std::cerr << "[Error] There is no argument named `" << key << "`!" << std::endl;
        std::exit(134);
      }
    }
  }
};

} // end namespace libgu

#endif // end header guard
