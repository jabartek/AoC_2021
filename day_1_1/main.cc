#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>

int main(int argc, const char *argv[]) {
  if (argc != 2) {
    std::cout << "Please provide input file name as one and only argument\n";
    std::exit(EXIT_FAILURE);
  }
  std::ifstream input{};
  try {
    input.open(argv[1]);
  } catch (const std::exception &e) {
    std::cout << "Error when opening input file:\n" << e.what() << "\n";
    std::exit(EXIT_FAILURE);
  }

  unsigned long long counter{0};
  std::string line{};
  auto last = std::numeric_limits<long long>::max();
  while (std::getline(input, line)) {
    auto current = std::stoll(line);
    counter += current > last;
    last = current;
  }
  std::cout << counter << "\n";
}