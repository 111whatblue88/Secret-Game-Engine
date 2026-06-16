#include "../common/common.hpp"

#include <format>
#include <string>
#include <vector>
#include <unordered_map>
#include <functional>
#include <nlohmann/json.hpp>

using namespace secret;
using namespace output;
using namespace filesystem;

using json = nlohmann::json;

int main() {

  std::string input = "";

  locateToEngineRoot();
  filesystem::execCommand("SecretCLI/build/SecretCLIParser/bin/SecretCLIParser context clear");

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

    std::ifstream f("SecretCLI/cliInfo.json");
    json cliInfo = json::parse(f);

    if (cliInfo["context"]["project"] == "") {
      filesystem::execCommand(std::format("SecretCLI/build/SecretCLIParser/bin/SecretCLIParser {}", input).c_str());
      continue;
    } 
    std::string projectContext = cliInfo["context"]["project"];
    filesystem::execCommand(std::format("SecretCLI/build/SecretCLIParser/bin/SecretCLIParser project {} {}", input, projectContext).c_str());



  }
  
}







