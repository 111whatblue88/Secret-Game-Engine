
#include "../common.hpp" 
#include "../../../engine/vendored/json/single_include/nlohmann/json.hpp" 

using namespace secret; 
using namespace output; 
using json = nlohmann::json;

void output::printColor(std::string string, color color) {
  switch (color) {
    case color::red: {
      std::cout << "\x1b[31m" << string << "\x1b[0m";
      break;
    }
    case color::green: {
      std::cout << "\x1b[32m" << string << "\x1b[0m";
      break;
    }
    case color::blue: {
      std::cout << "\x1b[34m" << string << "\x1b[0m";
      break;
    }
    case color::white: {
      std::cout << "\x1b[37m" << string << "\x1b[0m";
      break;
    }
  }
}
void output::clearTerm() {
  std::cout << "\x1b[2J\x1b[H";
}
void output::printSplash(color color) {

/*
   ____                __  _______   ____
  / __/__ ___________ / /_/ ___/ /  /  _/
 _\ \/ -_) __/ __/ -_) __/ /__/ /___/ /
/___/\__/\__/_/  \__/\__/\___/____/___/
*/

  filesystem::locateToEngineRoot();

  std::ifstream f("SecretCLI/cliInfo.json");
  json cliInfo = json::parse(f);

  output::printColor("   ____                __  _______   ____\n", color::white);
  output::printColor("  / __/__ ___________ / /_/ ___/ /  /  _/\n", color::white);
  output::printColor(" _\\ \\/ -_) __/ __/ -_) __/ /__/ /___/ / \n", color::white);
  output::printColor("/___/\\__/\\__/_/  \\__/\\__/\\___/____/___/ \n\n", color::white);

  std::string name = cliInfo["releaseName"];
  std::string desc = cliInfo["description"];
  std::string ver = cliInfo["ver"];

  output::printColor(std::format("> {}\n",name),color::blue);
  output::printColor(std::format("> {}\n",desc),color::blue);
  output::printColor(std::format("> {}\n\n",ver),color::blue);

}

