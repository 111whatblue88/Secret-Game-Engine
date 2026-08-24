#include "COutput.hpp"
#include "../secret.hpp"

#include <ctime>
#include <format>
#include <cstring>
#include <string>
#include <iostream>

using namespace secret ;
using namespace console;

void COutput::LogError(std::string system, std::string errMsg) {
  std::time_t time = std::time(NULL);
  OH::OutputLog(std::format("{} ERROR", system), errMsg, OH::Color::RED);
}
void COutput::LogDescriptive(std::string system, std::string msg) {

}
void COutput::LogWarning(std::string system, std::string warMsg) {
  std::time_t time = std::time(NULL);
  OH::OutputLog(std::format("{} WARNING", system), warMsg, OH::Color::YELLOW);
}
void COutput::Log(std::string system, std::string msg) {
  std::time_t time = std::time(NULL);
  OH::OutputLog(system, msg, OH::Color::WHITE);
}

void COutput::LogSDLError() {
  if (strcmp(SDL_GetError(), "")) {
    std::time_t time = std::time(NULL);
    OH::OutputLog("SDL ERROR", SDL_GetError(), OH::Color::WHITE);
  }
}

