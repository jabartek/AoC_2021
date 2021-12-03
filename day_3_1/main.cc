#include "../include/file.hpp"

#include <cstddef>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace janowski::aoc_2021;

int main(int argc, const char *argv[]) {
  auto input = getFile(argc, argv);

  long long gamma{0};
  long long epsilon{0};
  long long counter{0};
  std::vector<long long> sums_by_bit{};
  std::string line{};
  while (std::getline(input, line)) {
    if (counter == 0) {
      sums_by_bit.resize(line.length(), 0);
    }
    for (std::size_t i = 0; i < sums_by_bit.size(); ++i) {
      sums_by_bit[i] += line[i] == '1';
    }
    ++counter;
  }

  unsigned long long denominator = 1 << (sums_by_bit.size() - 1);
  for (auto v : sums_by_bit) {
    gamma += (v >= counter / 2) * denominator;
    epsilon += (v < counter / 2) * denominator;
    denominator /= 2;
  }

  std::cout << gamma << " " << epsilon << " " << gamma * epsilon << "\n";
}