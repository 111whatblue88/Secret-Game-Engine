#include "../ELOgine.hpp"

#include <SDL3/SDL_timer.h>
#include <functional>
#include <string>

namespace elo {
namespace core {

Engine::EngineOptions Engine::options = {
  60
};

std::function<void()> Engine::update = []() {

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


  while (!input::InputSys::quit) {


  elo::input::InputSys::Input();

  update();

  rend::RenderSys::render(); 


  }

  // log exit
  return true;

}

}

}



