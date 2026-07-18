#pragma once

#include <vector>
#include <GL/glew.h>
#include <string>
#include <unordered_map>

#include "../../../vendored/glm/glm/glm.hpp"
#include "../../../vendored/glm/glm/gtc/matrix_transform.hpp"
#include "../../general/general.hpp"

namespace secret {
namespace rend {

class Shader {
private:
  unsigned int ID;
  std::string shaderSource;
  
  std::unordered_map<std::string, int> uniformLocationCache;

public:

  Shader();
  Shader(const std::string& shaderPath);

  void Bind();
  void Unbind();

  unsigned int GetUniformLocation(const std::string& name);

  void setUniform4f(const std::string& name, Vec4 vec4);
  void setUniformMat4f(const std::string& name, const glm::mat4& mat4);

  struct ShaderFileSources {
    std::string vertexSource;
    std::string fragmentSource;
  };

  static ShaderFileSources parseShader(const std::string& shaderPath);

  static unsigned int compileShader(unsigned int type, const std::string& source);
  static unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader);

};

}
}
