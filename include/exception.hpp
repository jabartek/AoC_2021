#pragma once

#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>

namespace janowski::aoc_2021 {
inline void handleException(const std::exception &e,
                            const std::string &message) {
  std::cout << message << "\nException:\n" << e.what() << "\n";
  std::exit(EXIT_FAILURE);
}
} // namespace janowski::aoc_2021