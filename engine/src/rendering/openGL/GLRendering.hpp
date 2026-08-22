#ifndef _GLRENDERING_HPP
#define _GLRENDERING_HPP

#include "../../general/general.hpp"
#include "../../../vendored/SDL/src/include/SDL3/SDL.h"
#include "../../../vendored/SDL/src_image/include/SDL3_image/SDL_image.h"
#include "../../../vendored/SDL/src_ttf/include/SDL3_ttf/SDL_ttf.h"

#include "../../../vendored/glm/glm/glm.hpp"
#include "../../../vendored/glm/glm/gtc/matrix_transform.hpp"
#include <SDL3/SDL_video.h>
#include <unordered_map>
#include <vector>
#include <string>
#include <map>

namespace secret {
namespace rend {

class openGL {
public:

  openGL();
  static bool Init(float w, float h);

  static SDL_GLContext GLContext;

  // rendering

  static void renderTriangleTest();
  static void renderTriangle();

  // error

  static bool errorCheck(std::string file, int line);
  static void errorClear();


  static glm::mat4 windowProjection;

};

}
}

#endif
