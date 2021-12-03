#pragma once

#include "exception.hpp"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdexcept>

namespace janowski::aoc_2021 {
std::ifstream getFile(int argc, const char *argv[]) {
  if (argc != 2) {
    std::cout << "Please provide input file name as one and only argument\n";
    std::exit(EXIT_FAILURE);
  }
  std::ifstream input{};
  try {
    input.open(argv[1]);
  } catch (const std::exception &e) {
    handleException(e, "Error when opening input file");
  }
  return input;
}
} // namespace janowski::aoc_2021