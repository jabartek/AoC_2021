#include <iterator>
#include <list>
#include <map>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "../include/file.hpp"

using namespace janowski::aoc_2021;

using I = long long;

std::vector<I> split(const std::string &src, const char delimiter) {
  std::vector<I> result{};
  std::stringstream ss{src};
  std::string item{};

  while (std::getline(ss, item, delimiter)) {
    result.push_back(std::stoll(item));
  }

  return result;
}

class Board {
 public:
  std::vector<I> vertical_sums;
  std::vector<I> horizontal_sums;
  std::map<I, std::pair<I, I>> map;
  bool done{false};
  I total{0};

  Board(I dim) : vertical_sums(dim, dim), horizontal_sums(dim, dim) {}

 private:
};

int main(int argc, const char *argv[]) {
  auto input = getFile(argc, argv);

  std::vector<std::string> lines{};
  {
    std::string line{};
    while (std::getline(input, line)) {
      if (line.empty()) {
        continue;
      }
      lines.emplace_back(std::move(line));
    }
  }

  auto bingo_sequence = split(lines.front(), ',');

  lines.erase(lines.begin());

  I bingo_dim{};

  {
    std::stringstream ss{lines.front()};
    std::vector<I> numbers{};
    std::copy(std::istream_iterator<I>(ss), std::istream_iterator<I>(),
              std::back_inserter(numbers));
    bingo_dim = numbers.size();
  }
  std::list<Board> boards;
  for (auto i = 0ul; i < lines.size(); i += bingo_dim) {
    Board b{bingo_dim};
    for (auto y = 0ul; y < bingo_dim; ++y) {
      std::stringstream ss{lines[i + y]};
      for (auto x = 0ul; x < bingo_dim; ++x) {
        I val{};
        ss >> val;
        b.total += val;
        b.map[val] = std::make_pair(x, y);
      }
    }
    boards.emplace_back(std::move(b));
  }

  struct {
    I val{}, total{};

  } result;
  I done_counter{0};

  for (auto v : bingo_sequence) {
    for (auto b_it = boards.begin(); b_it != boards.end(); ++b_it) {
      auto &b = *b_it;
      if (b.done) {
        continue;
      }
      auto it = b.map.find(v);
      if (it == b.map.end()) {
        continue;
      }
      auto [x, y] = it->second;
      --b.vertical_sums[x];
      --b.horizontal_sums[y];
      b.total -= v;
      b.map.erase(it);
      if (b.vertical_sums[x] == 0 || b.horizontal_sums[y] == 0) {
        ++done_counter;
        b.done = true;
        result.val = v;
        result.total = b.total;
        if (done_counter == boards.size()) {
          break;
        }
      }
    }
    if (done_counter == boards.size()) {
      break;
    }
  }
  std::cout << result.total << '\t' << result.val << '\t'
            << result.total * result.val << '\n';
}