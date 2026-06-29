#include "../secret.hpp"
#include "../../vendored/SDL/src/include/SDL3/SDL.h"
#include "../../vendored/SDL/src_ttf/include/SDL3_ttf/SDL_ttf.h"
#include "openGL/GLRendering.hpp"

#include <SDL3/SDL_init.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_render.h>
#include <format>
#include <cstddef>
#include <cstdint>
#include <string>
#include <sys/types.h>
#include <unordered_map>

namespace secret {
namespace rend {

using namespace console;

std::vector<RenderSys::RenderCall> RenderSys::CallList = std::vector<RenderSys::RenderCall>();

using namespace ecs;

SDL RenderSys::m_SDL = SDL();

bool RenderSys::renderGL() {


  // proccess callbacks
  for (size_t i = 0; i < CallList.size(); i++) {
   
    glClear(GL_COLOR_BUFFER_BIT);

    switch (CallList[i].type) {
      
      case CallType::GL_TESTTRIANGLE:
      openGL::renderTriangleTest();
      break;

    }
  }  
  CallList.clear();

  m_SDL.renderPresentGL();
  return true;  
};

bool RenderSys::renderSDL() {

  m_SDL.setRenderColor(Color{0,0,0});
  m_SDL.renderClear();

  // proccess callbacks
  for (size_t i = 0; i < CallList.size(); i++) {
    
    switch (CallList[i].type) {
      
      case CallType::SDL_RBOX: {
        m_SDL.renderBox(
          CallList[i].PD.pos,
          CallList[i].SD.width,
          CallList[i].SD.height,
          CallList[i].RD.color
        );
        break;
      }
      case CallType::SDL_RBOXFILL: {
        m_SDL.renderBoxFill(
          CallList[i].PD.pos,
          CallList[i].SD.width,
          CallList[i].SD.height,
          CallList[i].RD.color
        );
        break;
      }
      case CallType::SDL_RCIRCLE: {
        m_SDL.renderCircle(
          CallList[i].PD.pos,
          CallList[i].SD.radius,
          CallList[i].RD.color
        );
        break;
      }
      case CallType::SDL_RCIRCLEFILL:
        m_SDL.renderCircleFill(
          CallList[i].PD.pos,
          CallList[i].SD.radius,
          CallList[i].RD.color
        );
        break;
      case CallType::SDL_SETDRAWCOLOR:
        m_SDL.setRenderColor(CallList[i].RD.color);
        break;
      case CallType::SDL_RTEXTURE:
        m_SDL.renderTexture(
          CallList[i].RD.texture,
          CallList[i].RD.uv,
          CallList[i].RD.layer,
          SDL_FRect{
            CallList[i].PD.pos.x,
            CallList[i].PD.pos.y,
            CallList[i].SD.width,
            CallList[i].SD.height,
          }
        );
      break;
      case CallType::SDL_RLINE:
        m_SDL.renderLine(
          CallList[i].PD.pos,
          CallList[i].PD.pos2,
          CallList[i].RD.color
        );
      break;
      case CallType::SDL_RFULLTEXTURE:
        m_SDL.renderTextureFull(
          CallList[i].RD.texture,
          CallList[i].RD.layer,
          SDL_FRect{
            CallList[i].PD.pos.x,
            CallList[i].PD.pos.y,
            CallList[i].SD.width,
            CallList[i].SD.height,
          }
        );
      break;
      case CallType::SDL_RGEOMETRY:
        m_SDL.renderGeometry(
          CallList[i].GD.verticies, 
          CallList[i].GD.numVerticies, 
          CallList[i].GD.indices, 
          CallList[i].GD.numIndices
      );
      case CallType::SDL_RPOINTS:
        m_SDL.renderPoints(
          CallList[i].GD.points,
          CallList[i].GD.numPoints
      );
      break;
    }
  }  
  CallList.clear();

  m_SDL.renderPresent();
  return true;  
};


}

}


