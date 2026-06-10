#include "../secretCLI.hpp"

#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <format>
#include <cstdint>
#include <functional>
#include <string>
#include <fstream>
#include <iostream>
#include <string>

using namespace secret;
using namespace helpers;

using json = nlohmann::json;

void helpers::execCommand(const char* cmd) {
  std::string command = std::format("{} 2>&1", cmd);
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        return;
    }

    std::array<char, 256> buffer;

    while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
        std::cout << buffer.data();
        std::cout.flush();
    }

    int status = pclose(pipe);

    return;
}



void helpers::printColor(std::string string, color color) {
  switch (color) {
    case color::red: {
      std::cout << "\033[1;31m" << string << "\033[0m";
      break;
    }
    case color::green: {
      std::cout << "\033[1;32m" << string << "\033[0m";
      break;
    }
    case color::blue: {
      std::cout << "\033[1;34m" << string << "\033[0m";
      break;
    }
    case color::white: {
      std::cout << "\033[1;37m" << string << "\033[0m";
      break;
    }
  }
}
void helpers::clearTerm() {
  std::cout << "\033[2J\033[H";
}
void helpers::printSplash(color color) {

/*
   ____                __  _______   ____
  / __/__ ___________ / /_/ ___/ /  /  _/
 _\ \/ -_) __/ __/ -_) __/ /__/ /___/ /
/___/\__/\__/_/  \__/\__/\___/____/___/
*/



  std::ifstream f("../../cliInfo.json");
  json cliInfo = json::parse(f);

  helpers::clearTerm();
  helpers::printColor("   ____                __  _______   ____\n", color::white);
  helpers::printColor("  / __/__ ___________ / /_/ ___/ /  /  _/\n", color::white);
  helpers::printColor(" _\\ \\/ -_) __/ __/ -_) __/ /__/ /___/ / \n", color::white);
  helpers::printColor("/___/\\__/\\__/_/  \\__/\\__/\\___/____/___/ \n\n", color::white);

  std::string name = cliInfo["releaseName"];
  std::string desc = cliInfo["description"];
  std::string ver = cliInfo["ver"];

  helpers::printColor(std::format("> {}\n",name),color::blue);
  helpers::printColor(std::format("> {}\n",desc),color::blue);
  helpers::printColor(std::format("> {}\n\n",ver),color::blue);

}

