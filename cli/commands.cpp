#include "commands.hpp"
#include "../elogine.hpp"

#include <vector>
#include <string>
#include <unordered_map>
#include <functional>

using namespace elogine::terminal;

Commands::Commands(std::string test) {

  // add commands here
  commands["quit"] = quitCMD;
  commands["clear"] = clearCMD;
  commands["help"] = helpCMD;

  quit = false;

}

void Commands::processCommands(std::vector<std::string> tokens) {

  for (size_t i = 0; i < tokens.size(); i++) {
    
    bool validCommand = false;

    for (auto commands : commands) {

      if (tokens[i] == commands.first) {
        commands.second();
        validCommand = true;

        //process command options

        break;
      } 

    }
      if (!validCommand) {
        std::cout << Output::colorString("Command: ", Output::Color::red) << tokens[i] 
          << Output::colorString(" Not known\n", Output::Color::red);
        
        break;
      }

  }

}

void Commands::printSplash() {
  std::cout << "   ______   ____       _            _______   ____" << "\n";
  std::cout << "  / __/ /  / __ \\___ _(_)__  ___   / ___/ /  /  _/" << "\n";
  std::cout << " / _// /__/ /_/ / _ `/ / _ \\/ -_) / /__/ /___/ /" << "\n";
  std::cout << "/___/____/\\____/\\_, /_/_//_/\\__/  \\___/____/___/" << "\n";
  std::cout << "               /___/" << "\n";
  std::cout << Output::colorString("ELOgine CLI - ver. ALPHA 0.1\n", Output::Color::white);
}

void Commands::quitCMD() {
  quit = true;
}

void Commands::clearCMD() {
  Output::clearTerminal();
  printSplash();
}

void Commands::helpCMD() {

}



