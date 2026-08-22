#pragma once

#include <string>

namespace secret {

class COutput {
public:

  static void Log(std::string system, std::string msg);
  static void LogWarning(std::string system, std::string msg);
  static void LogError(std::string system, std::string msg);
  static void LogSDLError();

};
};






