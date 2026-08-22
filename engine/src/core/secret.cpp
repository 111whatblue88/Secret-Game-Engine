#include "../secret.hpp"

#include <format>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_timer.h>
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
  COutput::LogWarning("ENGINE", std::format("Exiting early on next cycle. Exit message: \"{}\"", msg), OH::Color::YELLOW);

  engineExit = true;
};

bool Engine::init(int width, int height, std::string name) {
#ifdef DEBUG
  Timer initTimer;
  initTimer.start();
#endif
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
    COutput::logError("failed init SDL");
    COutput::logSDLError();
  }
  if (Engine::options.renderingAPI == RenderingAPIs::openGL) {
    if (!rend::openGL::Init(width, height)) {
      COutput::logError("failed to init openGL");
    }
  }

  audio::AudioSys::Init();

#ifdef DEBUG
  debug_log("ENGINE", std::format("engine took {}ms to initialize", std::to_string(initTimer.end())));
#endif

  COutput::logCustom("ENGINE", "Engine Intinalized");

  return true;
}

bool Engine::run() {

  if (!rend::RenderSys::m_SDL.wasInit()) {
    COutput::logCustom("FATAL ERROR", 
      "Renderer and window do not exist. Maybe the init function was not called?",
      COutput::MsgColor::red
    );
    earlyExit("No renderer or window");
  }

  if (!engineExit) {
    COutput::logCustom("ENGINE", "Starting...");
    
    filesystem::locateToEngineRoot();
    std::ifstream f("engine/engineInfo.json");
    json engineInfo = json::parse(f);
    COutput::logCustom("ENGINE", engineInfo["releaseName"]);
    COutput::logCustom("ENGINE", engineInfo["description"]);
    std::string version = engineInfo["ver"];
#ifdef DEBUG
    COutput::logCustom("ENGINE", std::format("Ver.({}): {}", "DEBUG", version));
#else
    COutput::logCustom("ENGINE", std::format("Ver.({}): {}", "RELEASE", version));
#endif

    switch (options.renderingAPI) {
      case secret::core::RenderingAPIs::SDL: 
        COutput::logCustom("ENGINE", "Rendering API: SDL3");
        break;
      case secret::core::RenderingAPIs::openGL: 
        COutput::logCustom("ENGINE", "Rendering API: openGL");
        break;
    } 

  } else {
    COutput::logCustom("ENGINE", "Exit request detected, aborting startup...", COutput::MsgColor::yellow);
  }

  uint32_t lastFrameTime = SDL_GetTicks();
  while (!engineExit) {

    COutput::logSDLError();

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

  COutput::logCustom("ENGINE", "Exiting...");

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



