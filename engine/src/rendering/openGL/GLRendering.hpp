#ifndef _GLRENDERING_HPP
#define _GLRENDERING_HPP

#include "../../general/general.hpp"
#include "../../../vendored/SDL/src/include/SDL3/SDL.h"
#include "../../../vendored/SDL/src_image/include/SDL3_image/SDL_image.h"
#include "../../../vendored/SDL/src_ttf/include/SDL3_ttf/SDL_ttf.h"

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
  static bool Init();

  static SDL_GLContext GLContext;

  // rendering

  static void renderTriangleTest();
  static void renderTriangle();

  // shaders

  struct shaderFileSources {
    std::string vertexSource;
    std::string fragmentSource;
  };

  static shaderFileSources parseShader(const std::string& shaderPath);

  static unsigned int compileShader(unsigned int type, const std::string& source);
  static unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader);

  // error

  static bool errorCheck(std::string file, int line);
  static void errorClear();

private:

};

}
}

#endif
