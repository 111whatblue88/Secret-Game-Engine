#include "GLRendering.hpp"
#include "../../secret.hpp"
#include "../../../vendored/SDL/src/include/SDL3/SDL.h"
#include "../../../vendored/SDL/src_image/include/SDL3_image/SDL_image.h"
#include "../../../vendored/SDL/src_ttf/include/SDL3_ttf/SDL_ttf.h"
#include "../../../vendored/SDL/src_mixer/include/SDL3_mixer/SDL_mixer.h"
#include "vertex.hpp"
#include "shader.hpp"

#include <GL/gl.h>
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

  return true;

}

void openGL::renderTriangleTest() {

  float triangle[] = {
    -5.0f, -5.0f,
    5.0f, -5.0f,
    5.0f, 5.0f,
    -5.0f, 5.0f,

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

  Shader shader("assets/shaders/basic.shader");
  
  shader.Bind();

  glm::mat4 proj = glm::ortho(-225.0f, 225.0f, -255.0f, 255.0f, -1.0f, 1.0f);
  glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-100, 0, 0));
  glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0,100,0 ));

  glm::mat4 mvp = proj*view*model;

  shader.setUniformMat4f("u_MVP", mvp);
  shader.setUniform4f("u_Color", Vec4{1.0, 0.0, 0.0, 1.0});

  RenderSys::CallList.push_back(
    RenderSys::RenderCall{
      RenderSys::CallType::GENERAL_VERTEX_RENDER,
      RenderSys::PositionalData{},
      RenderSys::SizeData{},
      RenderSys::RenderingData{},
      RenderSys::GeometryDataOLD{},
      RenderSys::GeometryData{va,ib,shader}
    }
  );

}

void openGL::renderTriangle() {

}

bool openGL::errorCheck(const char* file, const int line) {
  while (GLenum error = glGetError()) {
    switch (error) {
      case GL_INVALID_ENUM:
        COutput::LogError("OPENGL", "invalid enum", file, line);
        break;
      case GL_INVALID_VALUE:
        COutput::LogError("OPENGL", "invalid value", file, line);
        break;
      case GL_INVALID_OPERATION:
        COutput::LogError("OPENGL", "invalid operation", file, line);
        break;
      case GL_INVALID_FRAMEBUFFER_OPERATION:
        COutput::LogError("OPENGL", "invalid framebuffer operation", file, line);
        break;
      case GL_OUT_OF_MEMORY:
        COutput::LogError("OPENGL", "out of memory", file, line);
        break;
      case GL_STACK_UNDERFLOW:
        COutput::LogError("OPENGL", "stack underflow", file, line);
        break;
      case GL_STACK_OVERFLOW:
        COutput::LogError("OPENGL", "stack overflow", file, line);
      case GL_NO_ERROR:
        return false;
        break;
      default:
        COutput::LogError("OPENGL", "unknown error", file, line);
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

