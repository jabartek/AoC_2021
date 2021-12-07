#include <algorithm>
#include <limits>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

#include "../include/file.hpp"

using namespace janowski::aoc_2021;

using I = double;

std::vector<I> split(const std::string &src, const char delimiter) {
  std::vector<I> result{};
  std::stringstream ss{src};
  std::string item{};

  while (std::getline(ss, item, delimiter)) {
    result.push_back(std::stoll(item));
  }

  return result;
}

int main(int argc, const char *argv[]) {
  I sum = 0;
  for (I i = 0; i < 100; ++i) {
    sum += i;
    std::cout << i << "\t" << sum << std::endl;
  }
  auto input = getFile(argc, argv);

  std::string line{};
  std::getline(input, line);
  auto sequence = split(line, ',');

  auto max_elem = *std::max_element(sequence.begin(), sequence.end());
  auto min_elem = *std::min_element(sequence.begin(), sequence.end());

  struct {
    I sum{std::numeric_limits<I>::max()}, value{0};
  } result;

  for (auto i = min_elem; i <= max_elem; ++i) {
    auto sum = std::accumulate(sequence.begin(), sequence.end(), 0,
                               [i](I curr_sum, I element) {
                                 auto diff = std::abs(element - i);
                                 return curr_sum + (diff * (diff / 2 + 0.5));
                               });
    if (sum < result.sum) {
      result.sum = sum;
      result.value = i;
    }
  }
  std::cout << (long long)result.sum << std::endl;
}