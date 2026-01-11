#include "../../engine/src/elogine.hpp"

#include <string>
#include <vector>

using namespace elogine::terminal;

/*
splash screen logo
   ______   ____       _            _______   ____ done
  / __/ /  / __ \___ _(_)__  ___   / ___/ /  /  _/ done
 / _// /__/ /_/ / _ `/ / _ \/ -_) / /__/ /___/ / done
/___/____/\____/\_, /_/_//_/\__/  \___/____/___/ done
               /___/ done
*/

void printSplash() {
  std::cout << "   ______   ____       _            _______   ____" << "\n";
  std::cout << "  / __/ /  / __ \\___ _(_)__  ___   / ___/ /  /  _/" << "\n";
  std::cout << " / _// /__/ /_/ / _ `/ / _ \\/ -_) / /__/ /___/ /" << "\n";
  std::cout << "/___/____/\\____/\\_, /_/_//_/\\__/  \\___/____/___/" << "\n";
  std::cout << "               /___/" << "\n";
  std::cout << Output::colorString("ELOgine CLI - ver. ALPHA 0.1\n", Output::Color::white);
}

int main() {

  Output::clearTerminal();
  printSplash();

  std::string input;
  std::vector<std::string> tokens;

  while (input != "quit") {

    input = Input::getInput(Output::colorString(">", Output::Color::white));
    tokens = Input::tokenize(input);

  }

}
