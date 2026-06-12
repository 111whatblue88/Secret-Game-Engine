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

  std::string input = "";

  clearTerm();
  printSplash(color::blue);

  while (true) {

    printColor("> ", color::blue);
    std::getline(std::cin >> std::ws, input);

    if (input == "quit" || input == "exit") {
      return 0;
    }
    if (input == "clear") {
      clearTerm();
      printSplash(color::blue);
      continue;
    }

    locateToEngineRoot();
    filesystem::execCommand(std::format("SecretCLI/build/SecretCLIParser/bin/SecretCLIParser {}", input).c_str());



  }
  
}







