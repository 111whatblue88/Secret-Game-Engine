#include "../common/common.hpp"

#include <format>
#include <string>
#include <vector>
#include <unordered_map>
#include <functional>

using namespace secret;
using namespace output;
using namespace filesystem;

int main() {

  std::cout << "hello?";

  locateToEngineRoot();

  /*

  std::string input;

  clearTerm();
  printSplash(color::blue);

  while (true) {

    printColor("> ", color::blue);
    std::getline(std::cin >> std::ws, input);

    if (input == "clear") {
      clearTerm();
      continue;
    }
    if (input == "quit" || "exit") {
      return 0;
    }

    filesystem::execCommand(std::format("SecretCLI/build/SecretCLIParser/bin/SecretCLIParser {}", input).c_str());

  }
  */
}







