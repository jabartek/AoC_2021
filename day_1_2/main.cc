#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <list>
#include <string>

inline void handleException(const std::exception &e,
                            const std::string &message) {
  std::cout << message << "\nException:\n" << e.what() << "\n";
  std::exit(EXIT_FAILURE);
}

int main(int argc, const char *argv[]) {
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

  unsigned long long counter{0};
  std::list<long long> window{};
  std::string line{};
  while (std::getline(input, line)) {
    if (window.size() >= 4) {
      window.pop_front();
    }
    window.emplace_back(std::stoll(line));
    counter += window.back() > window.front() && window.size() >= 4;
  }
  std::cout << counter << "\n";
}