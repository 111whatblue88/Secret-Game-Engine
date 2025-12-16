
#include "../../engine/src/elogine.hpp"

#include <iostream>
#include <string>
#include <vector>

void printSplash();

void printHelp();

void proccessTokens(std::vector<std::string> inTokens);

int main() {

  using namespace elo;

  std::string ans;

  printSplash();

  do {

    ans = TermInput::getInput(TermOutput::colorString(
        "waiting for input: ", TermOutput::Color::white));

    proccessTokens(TermInput::tokenize(ans));

  } while (ans != "quit" && ans != "exit");
}

void printSplash() {

  elo::TermOutput::clear();

  std::cout << " ________  _____       ___            _                  \n";
  std::cout << "|_   __  ||_   _|    .'   `.         (_)                 \n";
  std::cout << "  | |_ \\_|  | |     /  .-.  \\ .--./) __   _ .--.  .---.  \n";
  std::cout << "  |  _| _   | |   _ | |   | |/ /'`\\;[  | [ `.-. |/ /__\\ \n";
  std::cout
      << " _| |__/ | _| |__/ |\\  `-'  /\\ \\._// | |  | | | || \\__., \n";
  std::cout << "|________||________| `.___.' .',__` [___][___||__]'.__.' \n";
  std::cout << "   ______  _____     _____  ( ( __))                     \n";
  std::cout << " .' ___  ||_   _|   |_   _|                              \n";
  std::cout << "/ .'   \\_|  | |       | |                                \n";
  std::cout << "| |         | |   _   | |                                \n";
  std::cout << "\\ `.___.'\\ _| |__/ | _| |_                               \n";
  std::cout << " `.____ .'|________||_____|                              \n\n";
  std::cout << "ELOgine CLI Ver. 0.1-ALPHA\n";
  std::cout << "type \"help\" for a list of commands\n\n";
}

void printHelp() {

  std::cout << "\n----[GENERAL]----\n";
  std::cout << "clear - clears the screen\n";
  std::cout << "exit/quit - leave the program\n";
  std::cout << "help - this menu\n";

  std::cout << "\n----[PROJECT]----[INCOMPLETE]\n";
  std::cout << "project create - prompts you to create a new project\n";
  std::cout << "options are: -n {NAME} - doesnt ask for a name and uses this "
               "provided one. -b - creates a bare project, no CMakeListsFile "
               "or other helpers.\n";
  std::cout << "project delete - promps you to delete a project.\n";
  std::cout << "options are: -n {NAME} - doesnt ask for a name and uses this "
               "provided one instead.\n";
  std::cout << "project {NAME} build - builds the given project with the "
               "CMakeLists file \n";
  std::cout << "options are: -c - builds clean, deletes the previous build "
               "files.  \n";
  std::cout << "project {NAME} run - runs the given project \n";
  std::cout << "project {NAME} version - fetches the version from the version "
               "file in the project \n";

  std::cout << "\n----[ELOGINE]----[INCOMPLETE]\n";
  std::cout << "elogine version - fetches the version of ELOgine installed\n\n";
}

void proccessTokens(std::vector<std::string> inTokens) {

  if (inTokens.size() <= 0) {
    return;
  }

  if (inTokens.size() == 1) {

    if (inTokens[0] == "clear") {
      printSplash();
      return;
    } else if (inTokens[0] == "exit" || inTokens[0] == "quit") {
      return;
    } else if (inTokens[0] == "help") {
      printHelp();
      return;
    }
  }

  using namespace elo;

  std::cout << TermOutput::colorString("command not known\n",
                                       TermOutput::Color::red);
}
