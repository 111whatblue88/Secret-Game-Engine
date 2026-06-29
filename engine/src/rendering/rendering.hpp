#ifndef _RENDERING_HPP
#define _RENDERING_HPP

#include "../general/general.hpp"
#include "../../vendored/SDL/src/include/SDL3/SDL.h"
#include "../../vendored/SDL/src_image/include/SDL3_image/SDL_image.h"
#include "../../vendored/SDL/src_ttf/include/SDL3_ttf/SDL_ttf.h"
#include "SDL/SDLRendering.hpp"
#include "openGL/GLRendering.hpp"

#include <unordered_map>
#include <vector>
#include <string>
#include <map>

namespace secret {
namespace rend {

class RenderSys {
public:

  enum class CallType {

    // SDL Calls
    SDL_RBOXFILL,
    SDL_RBOX,
    SDL_RCIRCLE,
    SDL_RCIRCLEFILL,
    SDL_RLINE,
    SDL_SETDRAWCOLOR,
    SDL_RTEXTURE,
    SDL_RFULLTEXTURE,
    SDL_RGEOMETRY,
    SDL_RPOINTS,

    // openGL calls

    GL_TESTTRIANGLE

  };

  struct PositionalData {
    Vec2 pos;
    Vec2 pos2;
  };
  struct SizeData {
    float width;
    float height;
    float radius;
  };
  struct RenderingData {
    Color color;
    SDL_Texture* texture;
    SDL_FRect uv;
    int layer;
  };
  struct GeometryData {
    SDL_Vertex* verticies;
    int numVerticies;
    int* indices;
    int numIndices;
    SDL_FPoint* points;
    int numPoints;
  };
  struct RenderCall {
    CallType type; 
    PositionalData PD;
    SizeData SD;
    RenderingData RD;
    GeometryData GD;
  };


  static SDL m_SDL;

  static bool renderSDL();
  static bool renderGL();

  static std::vector<RenderCall> CallList;

};

#endif

}
}
