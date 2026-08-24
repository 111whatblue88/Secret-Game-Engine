#include "../common/common.hpp"

#include <format>
#include <string>
#include <vector>
#include <unordered_map>
#include <functional>
#include "../../engine/vendored/json/single_include/nlohmann/json.hpp"

using namespace secret;
using namespace output;
using namespace filesystem;

using json = nlohmann::json;

int main() {

  std::string input = "";

  locateToEngineRoot();
  filesystem::execCommand("SecretCLI/build/SecretCLIParser/bin/Debug/SecretCLIParser context clear");

  clearTerm();
  printSplash(color::blue);

  std::ifstream cliInfoFile("SecretCLI/cliInfo.json");
  json cliInfo = json::parse(cliInfoFile);

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

    if (input == "context clear") {
      filesystem::execCommand("SecretCLI/build/SecretCLIParser/bin/Debug/SecretCLIParser context clear");
      continue;
    }

    std::ifstream contextFile("SecretCLI/var/context.json");
    json contextInfo = json::parse(contextFile);

    if (contextInfo["context"]["project"] == "") {
      filesystem::execCommand(std::format("SecretCLI/build/SecretCLIParser/bin/Debug/SecretCLIParser {}", input).c_str());
      continue;
    } 

    std::string projectContext = contextInfo["context"]["project"];
    filesystem::execCommand(std::format("SecretCLI/build/SecretCLIParser/bin/Debug/SecretCLIParser project {} {}", input, projectContext).c_str());

  }
  
}







