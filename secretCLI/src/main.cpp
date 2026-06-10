#include "secretCLI.hpp"

#include <string>
#include <vector>
#include <unordered_map>
#include <functional>

using namespace secret;
using namespace helpers;

int main() {

  std::string ans;

  clearTerm();
  printSplash(color::white);

  do {

    printColor("> ", color::blue);
    std::getline(std::cin >> std::ws, ans);

  } while (ans != "quit");

}







