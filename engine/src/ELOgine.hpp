#include "general/general.hpp"
#include "rend/rend.hpp"
#include "input/input.hpp"

#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>
#include <functional>

namespace elo {
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
  static bool run();

  static float deltaTime();

  static void wait(int ms);



private:

  static float m_deltaTime;

};

}
}




