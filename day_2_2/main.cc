#include <cstdlib>
#include <exception>
#include <fstream>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <sstream>
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

  // clang-format off
  std::map<std::string, std::function<void(long long, long long &, long long &, long long &)>>
      dictionary{
          {"forward",
           []([[maybe_unused]] auto value,
              [[maybe_unused]] auto &horizontal,
              [[maybe_unused]] auto &vertical,
              [[maybe_unused]] auto &aim) {
             horizontal += value;
             vertical += aim * value;
           }},
          {"down",
           []([[maybe_unused]] auto value, 
              [[maybe_unused]] auto &horizontal,
              [[maybe_unused]] auto &vertical,
              [[maybe_unused]] auto &aim) {
             aim += value;
           }},
          {"up",
           []([[maybe_unused]] auto value,
              [[maybe_unused]] auto &horizontal,
              [[maybe_unused]] auto &vertical,
              [[maybe_unused]] auto &aim) {
             aim -= value;
           }},
      };
  // clang-format on

  long long horizontal{0};
  long long vertical{0};
  long long aim{0};
  std::string line{};
  while (std::getline(input, line)) {
    std::istringstream stream(line);
    std::string command{};
    long long value{};
    stream >> command;
    stream >> value;
    dictionary.at(command)(value, horizontal, vertical, aim);
  }
  std::cout << vertical * horizontal << "\n";
}