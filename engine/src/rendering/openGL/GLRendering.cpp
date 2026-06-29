#include "../../secret.hpp"
#include "../../../vendored/SDL/src/include/SDL3/SDL.h"
#include "../../../vendored/SDL/src_ttf/include/SDL3_ttf/SDL_ttf.h"

#include <GL/gl.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <format>
#include <cstddef>
#include <cstdint>
#include <string>
#include <sys/types.h>
#include <unordered_map>

namespace secret {
namespace rend {

using namespace console;

SDL_GLContext openGL::GLContext = NULL;

bool openGL::Init() {
  if (!glewInit()) {
    return false;
  } else {
    return true;
  }
}

void openGL::renderTriangleTest() {

  glBegin(GL_TRIANGLES);

  glVertex2f(-0.5f, -0.5f);
  glVertex2f(0.5f, 0.5f);
  glVertex2f(0.5f, -0.5f);

  glEnd();

}

}
}

