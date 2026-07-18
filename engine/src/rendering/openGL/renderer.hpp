#pragma once

#include <vector>
#include <GL/glew.h>
#include <string>
#include <unordered_map>

#include "../../general/general.hpp"
#include "vertex.hpp"
#include "shader.hpp"

namespace secret {
namespace rend {

class Renderer {
private:

public:

  static void Clear();
  static void Draw(VertexArray va, IndexBuffer ib, Shader shader);

};












}
}
