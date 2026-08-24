#ifndef _GLRENDERING_HPP
#define _GLRENDERING_HPP

#include "../../general/general.hpp"
#include <SDL3/SDL.h>
#include "../../../vendored/SDL/src_image/include/SDL3_image/SDL_image.h"
#include "../../../vendored/SDL/src_ttf/include/SDL3_ttf/SDL_ttf.h"
#include "../../../vendored/SDL/src_mixer/include/SDL3_mixer/SDL_mixer.h"

#include <unordered_map>
#include <vector>
#include <string>
#include <map>

namespace secret {
namespace rend {

class openGL {
public:

  openGL();
  static bool Init();

  static SDL_GLContext GLContext;

  // rendering

  static void renderTriangleTest();
  static void renderTriangle();

  // error

  static bool errorCheck(std::string file, int line);
  static void errorClear();

private:

};

}
}

#endif
