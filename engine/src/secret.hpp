#include "general/general.hpp"
#include "rendering/rendering.hpp"
#include "rendering/openGL/GLRendering.hpp"
#include "rendering/SDL/SDLRendering.hpp"
#include "audio/audio.hpp"
#include "input/input.hpp"
#include "ecs/ecs.hpp"
#include "math/math.hpp"
#include "console/COutput.hpp"
#include "filesystem/filesystem.hpp"
#include "../vendored/SDL/src/include/SDL3/SDL.h"
#include "../vendored/SDL/src_ttf/include/SDL3_ttf/SDL_ttf.h"
#include "../vendored/SDL/src_mixer/include/SDL3_mixer/SDL_mixer.h"
#include "../vendored/SDL/src_image/include/SDL3_image/SDL_image.h"
#include "../vendored/glew/include/GL/glew.h"
#include <GL/gl.h>

#include <chrono>
#include <nlohmann/json.hpp>
#include <iostream>
#include <string>
#include <functional>

// macros

#ifdef DEBUG
#define debug_log(x, y) console::COutput::logCustom(std::format("DEBUG_{}", x), y, console::COutput::MsgColor::gray)
#else
#define debug_log(x, y)
#endif

namespace secret {
namespace core {

enum class RenderingAPIs {
  SDL,
  openGL
};

class Engine {
  struct EngineOptions {
    int fpsCap;
    RenderingAPIs renderingAPI;
  };
public:

  static EngineOptions options;

  static std::function<void()> update; 

  static bool init(int width, int height, std::string name);

  static void earlyExit(std::string msg);
  static void exit();

  static bool run();

  static float deltaTime();

  static void wait(int ms);

  class Timer {
  public:

    Timer();

    void start();
    Uint64 end();

  private:
    Uint64 startTick;
  };
  

private:

  static bool engineExit;

  static float m_deltaTime;

};

}
}




