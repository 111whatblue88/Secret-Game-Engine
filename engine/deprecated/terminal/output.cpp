#include "output.hpp"
#include <string>
#include <iostream>

std::string elogine::terminal::Output::colorString(std::string inString, Color color) {
 
  std::string outString;

  switch (color) {

    case elogine::terminal::Output::Color::red:
      outString = "\033[1;31m"+inString+"\033[0m";
      break;

    case elogine::terminal::Output::Color::green:
      outString = "\033[1;32m"+inString+"\033[0m";
      break;

    case elogine::terminal::Output::Color::yellow:
      outString = "\033[1;33m"+inString+"\033[0m";
      break;

    case elogine::terminal::Output::Color::blue:
      outString = "\033[1;34m"+inString+"\033[0m";
      break;

    case elogine::terminal::Output::Color::white:
      outString = "\033[1;37m"+inString+"\033[0m";
      break;

    default: 
      outString = "";
      break;

  }
  return outString;
}

void elogine::terminal::Output::log(std::string message, LogLevel logLevel) {

  std::string level;

  using namespace elogine::terminal;

  switch (logLevel) {
    
    case Output::LogLevel::normal:
      level = Output::colorString("[MESSAGE]", Output::Color::white);
      break;

    case Output::LogLevel::warning:
      level = Output::colorString("[WARNING]", Output::Color::yellow);
      break;

    case Output::LogLevel::error:
      level = Output::colorString("[ERROR]", Output::Color::red);
      break;
    
    default:
      level = Output::colorString("[MESSAGE]", Output::Color::white);
      break;

  }
  
  std::cout << level << " " << message << "\n";

}

void elogine::terminal::Output::clearTerminal() {

  std::cout << "\033[2J\033[H";

}


