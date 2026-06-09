#include "general/general.hpp"
#include "rend/rend.hpp"
#include "audio/audio.hpp"
#include "input/input.hpp"
#include "ecs/ecs.hpp"
#include "math/math.hpp"
#include "console/COutput.hpp"
#include "../vendored/SDL/src/include/SDL3/SDL.h"
#include "../vendored/SDL/src_ttf/include/SDL3_ttf/SDL_ttf.h"
#include "../vendored/SDL/src_image/include/SDL3_image/SDL_image.h"

#include <nlohmann/json.hpp>
#include <iostream>
#include <string>
#include <functional>

namespace huge {
namespace core {

class Engine {
  struct EngineOptions {
    int fpsCap;
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

private:

  static bool engineExit;

  static float m_deltaTime;

};

}
}




