#include "GLRendering.hpp"
#include "../../secret.hpp"
#include "../../../vendored/SDL/src/include/SDL3/SDL.h"
#include "../../../vendored/SDL/src_ttf/include/SDL3_ttf/SDL_ttf.h"
#include "vertex.hpp"
#include "shader.hpp"
#include "renderer.hpp"

#include "../../../vendored/glew/include/GL/glew.h"
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
  va.Bind();
  shader.Bind();
  ib.Bind();
  GLCheck(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
  va.Unbind();
  shader.Unbind();
  ib.Unbind();
}
