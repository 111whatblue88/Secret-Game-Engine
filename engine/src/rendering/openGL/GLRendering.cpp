#include "GLRendering.hpp"
#include "../../secret.hpp"
#include "../../../vendored/SDL/src/include/SDL3/SDL.h"
#include "../../../vendored/SDL/src_ttf/include/SDL3_ttf/SDL_ttf.h"
#include "vertex.hpp"

#include <GL/gl.h>
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

//TODO: add in error handling to GL functions

namespace secret {
namespace rend {

using namespace console;

SDL_GLContext openGL::GLContext = NULL;

bool openGL::Init() {

  if (glewInit() != GLEW_OK) {
    return false;
  }

  // TESTING REMOVE AFTER
 
  float triangle[] = {
    -0.5f, -0.5f,
    0.5f, -0.5f,
    0.5f, 0.5f,
    -0.5f, 0.5f,

  };
  unsigned int indices[] = {
    0, 1, 2,
    2, 3, 0
  };
  
  VertexArray va;

  VertexBuffer vb(triangle, 8*sizeof(float));
  IndexBuffer ib(indices, 6*sizeof(unsigned int));
  
  VertexBufferLayout layout;
  layout.Push(2, GL_FLOAT, false);
  va.AddLayout(vb, layout);

  filesystem::locateToEngineRoot();

  openGL::shaderFileSources shaders = parseShader("engine/assets/shaders/basic.shader");

  unsigned int shader = createShader(shaders.vertexSource, shaders.fragmentSource);
  glUseProgram(shader);
  
  int location = glGetUniformLocation(shader, "u_Color");
  glUniform4f(location, 1.0, 0.0, 0.0, 1.0);

  // END OF TEST AREA

  return true;

}

void openGL::renderTriangleTest() {

  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

}

void openGL::renderTriangle() {

}

unsigned int openGL::compileShader(unsigned int type, const std::string& source) {

  unsigned int id = glCreateShader(type);
  const char * src = source.c_str();

  glShaderSource(id, 1, &src, nullptr);
  glCompileShader(id);


  int result;
  glGetShaderiv(id, GL_COMPILE_STATUS, &result);
  if (!result) {
    int length;
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
    char* message = (char*)alloca(length*sizeof(char));
    glGetShaderInfoLog(id, length, &length, message);
    COutput::logCustom("SHADER", message);
    glDeleteShader(id);
    return 0;
  }

  return id;

}

unsigned int openGL::createShader(const std::string& vertexShader, const std::string& fragmentShader) {
 
  unsigned int program = glCreateProgram();
  unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
  unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

  glAttachShader(program, vs);
  glAttachShader(program, fs);
  
  glLinkProgram(program);
  glValidateProgram(program);

  glDeleteShader(vs);
  glDeleteShader(fs);

  return program;

}

openGL::shaderFileSources openGL::parseShader(const std::string& shaderPath) {

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

  return shaderFileSources{vertexSrc.str(), fragmentSrc.str()};

}

bool openGL::errorCheck(std::string file, int line) {
  while (GLenum error = glGetError()) {
    switch (error) {
      case GL_INVALID_ENUM:
        COutput::logCustom("OPENGL ERROR", std::format("(invalid enum) (file:{}) (line:{})", file, line), COutput::MsgColor::red);
        break;
      case GL_INVALID_VALUE:
        COutput::logCustom("OPENGL ERROR", std::format("(invalid value) (file:{}) (line:{})", file, line), COutput::MsgColor::red);
        break;
      case GL_INVALID_OPERATION:
        COutput::logCustom("OPENGL ERROR", std::format("(invalid operation) (file:{}) (line:{})", file, line), COutput::MsgColor::red);
        break;
      case GL_INVALID_FRAMEBUFFER_OPERATION:
        COutput::logCustom("OPENGL ERROR", std::format("(invalid framebuffer operation) (file:{}) (line:{})", file, line), COutput::MsgColor::red);
        break;
      case GL_OUT_OF_MEMORY:
        COutput::logCustom("OPENGL ERROR", std::format("(out of memory) (file:{}) (line:{})", file, line), COutput::MsgColor::red);
        break;
      case GL_STACK_UNDERFLOW:
        COutput::logCustom("OPENGL ERROR", std::format("(stack underflow) (file:{}) (line:{})", file, line), COutput::MsgColor::red);
        break;
      case GL_STACK_OVERFLOW:
        COutput::logCustom("OPENGL ERROR", std::format("(stack overflow) (file:{}) (line:{})", file, line), COutput::MsgColor::red);
      case GL_NO_ERROR:
        return false;
        break;
      default:
        COutput::logCustom("OPENGL ERROR", std::format("(unknown error: {}) (file:{}) (line:{})",error, file, line), COutput::MsgColor::red);
        break;
    }
  }
  return true;
}

void openGL::errorClear() {
  while (glGetError() != GL_NO_ERROR);
}

}
}

