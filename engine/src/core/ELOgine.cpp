#include "../ELOgine.hpp"

#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_timer.h>
#include <cstdint>
#include <functional>
#include <string>

namespace elo {
namespace core {

Engine::EngineOptions Engine::options = {
  60
};

std::function<void()> Engine::update = []() {

};

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
  if (rend::RenderSys::m_renderer.init(width, height, name)) {
    return false;
  }
  return true;
}

bool Engine::run() {

  // log init

  if (!SDL_WasInit(SDL_INIT_VIDEO)) {
    if (SDL_Init(SDL_INIT_VIDEO)) {
      //log error 
    } 
  }
  if (TTF_WasInit() == 0) {
    if (!TTF_Init()) {
      // log error
    }
  }

  uint32_t lastFrameTime = SDL_GetTicks();

  while (!input::InputSys::quit) {

    uint32_t currentFrameTime = SDL_GetTicks();
    m_deltaTime = (currentFrameTime-lastFrameTime)/1000.0;
    lastFrameTime = currentFrameTime;

    elo::input::InputSys::Input();

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



