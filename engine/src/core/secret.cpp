#include "../secret.hpp"

#include "../../vendored/SDL/src/include/SDL3/SDL.h"
#include "../../vendored/SDL/src_image/include/SDL3_image/SDL_image.h"
#include "../../vendored/SDL/src_ttf/include/SDL3_ttf/SDL_ttf.h"
#include "../../vendored/SDL/src_mixer/include/SDL3_mixer/SDL_mixer.h"

#include <filesystem>
#include <format>
#include <cstdint>
#include <functional>
#include <string>
#include <fstream>

namespace secret {
namespace core {

using json = nlohmann::json;
using namespace console;

Engine::EngineOptions Engine::options = {
  60,
  RenderingAPIs::SDL
};

std::function<void()> Engine::update = []() {};

bool Engine::engineExit = false;
float Engine::m_deltaTime = 0;

float Engine::deltaTime() {
  return m_deltaTime;
};

void Engine::wait(int ms) {
  SDL_Delay(ms);
};

void Engine::exit() {
  engineExit = true;
}
void Engine::earlyExit(std::string msg) {
  COutput::LogWarning("ENGINE", std::format("Exiting early on next cycle. Exit message: \"{}\"", msg));

  engineExit = true;
};

bool Engine::init(int width, int height, std::string name) {
#ifdef DEBUG
  Timer initTimer;
  initTimer.start();
#endif
  OH::EnableConsoleProcessing();
  
  COutput::Log("ENGINE", "Initializing engine...");

  if (!SDL_WasInit(SDL_INIT_VIDEO)) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
      COutput::LogError("ENGINE", "SDL_Init failed");
      COutput::LogSDLError();
    } 
  }
  if (TTF_WasInit() == 0) {
    if (!TTF_Init()) {
      COutput::LogError("ENGINE", "failed to start TTF");
      COutput::LogSDLError();
    }
  }

  if (!rend::RenderSys::m_SDL.init(width, height, name)) {
    COutput::LogError("ENGINE", "failed init SDL");
    COutput::LogSDLError();
  }
  if (Engine::options.renderingAPI == RenderingAPIs::openGL) {
    if (!rend::openGL::Init()) {
      COutput::LogError("ENGINE", "failed to init openGL");
    }
  }

  audio::AudioSys::Init();

#ifdef DEBUG
  debug_log("ENGINE", std::format("engine took {}ms to initialize", std::to_string(initTimer.end())));
#endif

  return true;
}

bool Engine::run() {

  if (!rend::RenderSys::m_SDL.wasInit()) {
    COutput::LogError("ENGINE FATAL", "Renderer and window do not exist. Maybe the init function was not called?");
    earlyExit("No renderer or window");
  }

  if (!engineExit) {
    COutput::Log("ENGINE", "Starting...");
    
    filesystem::locateToEngineRoot();
    std::ifstream f("engineInfo.json");
    json engineInfo = json::parse(f);
    COutput::Log("ENGINE", engineInfo["releaseName"]);
    COutput::Log("ENGINE", engineInfo["description"]);
    std::string version = engineInfo["ver"];
#ifdef DEBUG
    COutput::Log("ENGINE", std::format("Ver.({}): {}", "DEBUG", version));
#else
    COutput::Log("ENGINE", std::format("Ver.({}): {}", "RELEASE", version));
#endif

    switch (options.renderingAPI) {
      case secret::core::RenderingAPIs::SDL: 
        COutput::Log("ENGINE", "Rendering API: SDL3");
        break;
      case secret::core::RenderingAPIs::openGL: 
        COutput::Log("ENGINE", "Rendering API: openGL");
        break;
    } 

  } else {
    COutput::LogWarning("ENGINE", "Exit request detected, aborting startup...");
  }

  uint32_t lastFrameTime = SDL_GetTicks();
  while (!engineExit) {

    uint32_t currentFrameTime = SDL_GetTicks();
    m_deltaTime = (currentFrameTime-lastFrameTime)/1000.0;
    lastFrameTime = currentFrameTime;
    secret::input::InputSys::Input();
    ecs::EntitySys::update();
    update();

    if (options.renderingAPI == RenderingAPIs::openGL) {
      rend::RenderSys::renderGL(); 
    } else {
      rend::RenderSys::renderSDL(); 
    }
    
    uint32_t frametime = SDL_GetTicks() - currentFrameTime;
    if (frametime<1000/ options.fpsCap) {
      SDL_Delay((1000/options.fpsCap)-frametime);
    }
    
  }

  COutput::Log("ENGINE", "Exiting...");

  return true;

}

Engine::Timer::Timer():
  startTick(0)
{}
void Engine::Timer::start() {
  startTick = SDL_GetTicks();
}
Uint64 Engine::Timer::end() {
  return SDL_GetTicks() - startTick;
}

}

}



