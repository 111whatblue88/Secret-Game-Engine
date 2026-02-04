#include "input.hpp" 

#include <iostream>
#include <sstream>
#include <string>
#include <strstream>
#include <vector>

using namespace elogine::terminal;

std::string Input::getInput(std::string prompt) {

  std::string output;

  std::cout << prompt << " ";
  std::getline(std::cin, output);

  return output;

}

std::vector<std::string> Input::tokenize(std::string input) {

  std::vector<std::string> tokens;
  std::string token;

  std::stringstream stream(input);

  while (stream >> token) {
    tokens.push_back(token);
  }

  return tokens;

}
