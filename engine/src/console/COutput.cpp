#include "COutput.hpp"
#include "../secret.hpp"

#include <ctime>

using namespace secret;

void COutput::LogWarning(std::string system, std::string msg) {  
  std::time_t *currentTime;
  time(currentTime);
  OH::OutputLog(system, msg, OH::Color::YELLOW, currentTime);
}
void COutput::Log(std::string system, std::string msg) {
  std::time_t *currentTime;
  time(currentTime);
  OH::OutputLog(system, msg, OH::Color::WHITE, currentTime);
}
void COutput::LogError(std::string system, std::string msg) {
  std::time_t *currentTime;
  time(currentTime);
  OH::OutputLog(system, msg, OH::Color::RED, currentTime);
}
void COutput::LogSDLError() {
  std::time_t *currentTime;
  time(currentTime);
  OH::OutputLog(system, std::format("{}", SDL_GetError()), OH::Color::RED, currentTime);
}
