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
      filesystem::execCommand("SecretCLI/build/SecretCLIParser/bin/SecretCLIParser context clear");
      continue;
    }
    if (cliInfo["context"]["project"] == "") {
      filesystem::execCommand(std::format("SecretCLI/build/SecretCLIParser/bin/SecretCLIParser {}", input).c_str());
      continue;
    } 

    if (std::filesystem::exists("SecretCLI/var/context.json")) {
      std::ifstream contextFile("SecretCLI/var/context.json");
      json contextInfo = json::parse(contextFile);
      std::string projectContext = contextInfo["context"]["project"];
      filesystem::execCommand(std::format("SecretCLI/build/SecretCLIParser/bin/SecretCLIParser project {} {}", input, projectContext).c_str());
    } else {
      filesystem::execCommand(std::format("SecretCLI/build/SecretCLIParser/bin/SecretCLIParser {}", input).c_str());
    }

  }
  
}







