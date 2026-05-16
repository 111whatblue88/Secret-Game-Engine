#include "COutput.hpp"
#include "../HUGE.hpp"

#include <string>
#include <iostream>

using namespace huge;
using namespace console;

void COutput::logError(std::string errMsg) {
  std::cout << resolveColor(MsgColor::white) << "[ERROR] " << 
    resolveColor(MsgColor::red) << errMsg << resolveColor(MsgColor::reset) << "\n";
}
void COutput::logWarning(std::string warMsg) {
  std::cout << resolveColor(MsgColor::white) << "[WARNING] " << 
    resolveColor(MsgColor::yellow) << warMsg << resolveColor(MsgColor::reset) << "\n";
}
void COutput::log(std::string msg) {
  std::cout << resolveColor(MsgColor::white) << "[MSG] " << 
    resolveColor(MsgColor::white) << msg << resolveColor(MsgColor::reset) << "\n";
}

void COutput::log(std::string msg, MsgColor color) {
  std::cout << resolveColor(MsgColor::white) << "[MSG] " << 
    resolveColor(color) << msg << resolveColor(MsgColor::reset) << "\n";
}
std::string COutput::resolveColor(MsgColor color) {
  switch (color) {
    case MsgColor::red: {
      return "\e[0;31m";
      break;
    }
    case MsgColor::green: {
      return "\e[0;32m";
      break;
    }
    case MsgColor::yellow: {
      return "\e[0;33m";
      break;
    }
    case MsgColor::white: {
      return "\e[0;37m";
      break;
    }
    case MsgColor::reset: {
      return "\e[0m";
      break;
    }
  }
  return "";
}
