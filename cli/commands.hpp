#ifndef _COMMANDS_HPP 
#define _COMMANDS_HPP

#include <vector>
#include <string>
#include <unordered_map>
#include <functional>

  class Commands {
  public:

    Commands(std::string test);

    void processCommands(std::vector<std::string> tokens);

    static void printSplash();

    static bool quit;

  private:
    // add command functions here
    static void quitCMD();
    static void clearCMD();
    static void helpCMD();

    std::unordered_map<std::string, std::function<void()>> commands;

  };

#endif




