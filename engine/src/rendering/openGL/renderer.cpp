#include "GLRendering.hpp"
#include "../../secret.hpp"
#include "../../../vendored/SDL/src/include/SDL3/SDL.h"
#include "../../../vendored/SDL/src_ttf/include/SDL3_ttf/SDL_ttf.h"
#include "vertex.hpp"
#include "shader.hpp"
#include "renderer.hpp"

#include <GL/glew.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <filesystem>
#include <format>
#include <cstddef>
#include <cstdint>
#include <fstream>
#include <sstream>
#include <string>
#include <sys/types.h>
#include <unordered_map>

using namespace secret;
using namespace rend;

void Renderer::Clear() {
  GLCheck(glClear(GL_COLOR_BUFFER_BIT));
}
void Renderer::Draw(VertexArray va, IndexBuffer ib, Shader shader) {
  GLCheck(glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr));
}
