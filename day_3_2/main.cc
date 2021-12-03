#include "../include/file.hpp"

#include <algorithm>
#include <cstddef>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

using namespace janowski::aoc_2021;

int main(int argc, const char *argv[]) {
  auto input = getFile(argc, argv);

  std::vector<std::vector<bool>> lines{};
  std::string line{};
  while (std::getline(input, line)) {
    lines.emplace_back();
    for (auto c : line) {
      lines.back().push_back(c == '1');
    }
  }

  auto process = [](std::vector<std::vector<bool>> lines,
                    std::function<bool(const std::vector<bool> &,
                                       const std::vector<unsigned long long> &,
                                       std::size_t, std::size_t)>
                        pred) -> long long {
    long long result{0};
    auto width = lines.front().size();
    std::vector<unsigned long long> sums(width);
    for (auto i = 0ul; i < width; ++i) {
      for (auto j = 0ul; j < sums.size(); ++j) {
        sums[j] = std::count_if(
            lines.begin(), lines.end(),
            [&](const std::vector<bool> &line) { return line[j]; });
      }
      decltype(lines) filtered{};
      std::copy_if(lines.begin(), lines.end(), std::back_inserter(filtered),
                   [&](const std::vector<bool> &line) {
                     return pred(line, sums, lines.size(), i);
                   });
      if (filtered.size() > 0) {
        std::swap(lines, filtered);
      } else {
        break;
      }
    }
    unsigned long long denominator = 1 << (width - 1);
    for (auto v : lines[0]) {
      result += v * denominator;
      denominator /= 2;
    }
    return result;
  };

  auto oxy_pred = [](auto &line, auto &sums, auto line_count, auto i) {
    return line[i] == sums[i] * 2 >= line_count;
  };

  auto co2_pred = [](auto &line, auto &sums, auto line_count, auto i) {
    return line[i] == sums[i] * 2 < line_count;
  };

  auto oxy = process(lines, oxy_pred);
  auto co2 = process(lines, co2_pred);

  std::cout << oxy << " " << co2 << " " << oxy * co2 << "\n";
}