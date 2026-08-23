#include "GLRendering.hpp"
#include "../../secret.hpp"
#include "vertex.hpp"
#include "shader.hpp"

#include "../../../vendored/non-git/glew/include/GL/glew.h"
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

void Shader::Bind() {
  GLCheck(glUseProgram(ID));
}
void Shader::Unbind() {
  GLCheck(glUseProgram(0));
}

Shader::ShaderFileSources Shader::parseShader(const std::string& shaderPath) {

  enum class ShaderType {
    vertex, fragment
  };
  std::stringstream vertexSrc;
  std::stringstream fragmentSrc;
  std::string line;
  std::ifstream stream(shaderPath);
  ShaderType currentType;
  while (getline(stream, line)) {
    if (line.find("#shader") != std::string::npos) {
      if (line.find("vertex") != std::string::npos) {
        currentType = ShaderType::vertex;
      } else if (line.find("fragment") != std::string::npos) {
        currentType = ShaderType::fragment;
      }
    } else {
      switch (currentType) {
        case ShaderType::fragment:
          fragmentSrc << line << "\n";
          break;
        case ShaderType::vertex:
          vertexSrc << line << "\n";
          break;
      }
    } 
  }

  return ShaderFileSources{vertexSrc.str(), fragmentSrc.str()};

}

unsigned int Shader::compileShader(unsigned int type, const std::string& source) {

  unsigned int id = glCreateShader(type);
  const char * src = source.c_str();

  GLCheck(glShaderSource(id, 1, &src, nullptr));
  GLCheck(glCompileShader(id));


  int result;
  glGetShaderiv(id, GL_COMPILE_STATUS, &result);
  if (!result) {
    int length;
    GLCheck(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
    char* message = (char*)alloca(length*sizeof(char));
    GLCheck(glGetShaderInfoLog(id, length, &length, message));
    console::COutput::logCustom("SHADER", message);
    GLCheck(glDeleteShader(id));
    return 0;
  }

  return id;

}
unsigned int Shader::createShader(const std::string& vertexShader, const std::string& fragmentShader) {

  unsigned int program = glCreateProgram();
  unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
  unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

  GLCheck(glAttachShader(program, vs));
  GLCheck(glAttachShader(program, fs));
  
  GLCheck(glLinkProgram(program));
  GLCheck(glValidateProgram(program));

  GLCheck(glDeleteShader(vs));
  GLCheck(glDeleteShader(fs));

  return program;

}

Shader::Shader(const std::string& shaderPath)
  : shaderSource(shaderPath), ID(0) {
  ShaderFileSources source = parseShader(shaderSource);
 ID = createShader(source.vertexSource, source.fragmentSource);
 uniformLocationCache = {};
}

Shader::Shader() {
  shaderSource="";
  ID=0;
}

unsigned int Shader::GetUniformLocation(const std::string& name) {
  if (uniformLocationCache.find(name) != uniformLocationCache.end()) {
    return uniformLocationCache["name"];
  }
  int location = GLCheck(glGetUniformLocation(ID, name.c_str()));
  uniformLocationCache[name] = location;
  return location;
}

void Shader::setUniform4f(const std::string& name, Vec4 vec4) {
  GLCheck(glUniform4f(GetUniformLocation(name), vec4.x, vec4.y, vec4.z, vec4.w));
}
void Shader::setUniformMat4f(const std::string& name, const glm::mat4& mat4) {
  GLCheck(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &mat4[0][0]));
}

