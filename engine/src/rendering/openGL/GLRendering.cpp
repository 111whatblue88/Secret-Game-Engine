#include "GLRendering.hpp"
#include "../../secret.hpp"
#include "../../../vendored/SDL/src/include/SDL3/SDL.h"
#include "../../../vendored/SDL/src_ttf/include/SDL3_ttf/SDL_ttf.h"
#include "vertex.hpp"
#include "shader.hpp"

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
glm::mat4 openGL::windowProjection = {};

bool openGL::Init(float w, float h) {

  if (glewInit() != GLEW_OK) {
    return false;
  }

  glViewport(0,0,w,h);
  windowProjection = glm::ortho(0.0f,w,0.0f,h, -1.0f, 1.0f);

  return true;

}

void openGL::renderTriangleTest() {

  float triangle[] = {
    -50.0f, -50.0f,
    50.0f, -50.0f,
    50.0f, 50.0f,
    -50.0f, 50.0f,

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

  Shader shader("engine/assets/shaders/basic.shader");
  
  shader.Bind();

  shader.setUniformMat4f("u_MVP", windowProjection);
  shader.setUniform4f("u_Color", Vec4{1.0, 0.0, 0.0, 1.0});

  RenderSys::CallList.push_back(
    RenderSys::RenderCall{
      RenderSys::CallType::GENERAL_VERTEX_RENDER,
      RenderSys::PositionalData{},
      RenderSys::SizeData{},
      RenderSys::RenderingData{},
      RenderSys::GeometryDataOLD{},
      RenderSys::GeometryDataGL{va,ib,shader}
    }
  );

}

void openGL::renderTriangle() {

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

