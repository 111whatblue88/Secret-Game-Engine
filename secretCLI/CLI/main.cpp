#include "printingTools/PT.hpp"
#include "secretCLI.hpp"

#include <format>
#include <string>
#include <vector>
#include <unordered_map>
#include <functional>

using namespace secret;
using namespace helpers;

int main() {

  std::string ans;
  std::string responce;

  clearTerm();
  printSplash(color::white);

  do {

    printColor("> ", color::blue);
    std::getline(std::cin >> std::ws, ans);

    if (ans == "quit") {
      return 0;
    }

    if (ans == "clear") {
      helpers::clearTerm();
      continue;
    }

    execCommand(std::format("../parser/bin/secret {}", ans).c_str());

  } while (ans != "quit");

}







