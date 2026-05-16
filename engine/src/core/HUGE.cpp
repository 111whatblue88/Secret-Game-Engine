#include "../HUGE.hpp"

#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_timer.h>
#include <cstdint>
#include <functional>
#include <string>
#include <fstream>

namespace huge {
namespace core {

using json = nlohmann::json;
using namespace console;

Engine::EngineOptions Engine::options = {
  60
};

std::function<void()> Engine::update = []() {};

float Engine::m_deltaTime = 0;

float Engine::deltaTime() {
  return m_deltaTime;
};

void Engine::wait(int ms) {
  SDL_Delay(ms);
};

void Engine::earlyExit(std::string msg) {

  // print msg

  // set m_quit to true in InputSys
  //
};

bool Engine::init(int width, int height, std::string name) {
  COutput::log("Initializing engine...");

  if (!SDL_WasInit(SDL_INIT_VIDEO)) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
      COutput::logError("failed to start SDL");
      COutput::logError(SDL_GetError());
    } 
  }
  if (TTF_WasInit() == 0) {
    if (!TTF_Init()) {
      COutput::logError("failed to start TTF");
      COutput::logError(SDL_GetError());
    }
  }

  if (rend::RenderSys::m_renderer.init(width, height, name)) {
    return false;
  }
  return true;
}

bool Engine::run() {

  COutput::log("Loop started. Fetching engine data...");
  std::ifstream f("../../../engine/engineInfo.json");
  json engineInfo = json::parse(f);
  COutput::log(std::string("Name: ")+std::string(engineInfo["releaseName"]));
  COutput::log(std::string("Description: ")+std::string(engineInfo["description"]));
  COutput::log(std::string("Ver: ")+std::string(engineInfo["ver"]));


  uint32_t lastFrameTime = SDL_GetTicks();

  while (!input::InputSys::quit) {

    uint32_t currentFrameTime = SDL_GetTicks();
    m_deltaTime = (currentFrameTime-lastFrameTime)/1000.0;
    lastFrameTime = currentFrameTime;

    huge::input::InputSys::Input();

    ecs::EntitySys::update();
    update();

    rend::RenderSys::render(); 
    
    uint32_t frametime = SDL_GetTicks() - currentFrameTime;
    if (frametime<1000/ options.fpsCap) {
      SDL_Delay((1000/options.fpsCap)-frametime);
    }
    
  }

  // log exit
  return true;

}

}

}



