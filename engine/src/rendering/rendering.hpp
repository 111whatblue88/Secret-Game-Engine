#ifndef _RENDERING_HPP
#define _RENDERING_HPP

#include "../general/general.hpp"
#include "../../vendored/SDL/src/include/SDL3/SDL.h"
#include "../../vendored/SDL/src_image/include/SDL3_image/SDL_image.h"
#include "../../vendored/SDL/src_ttf/include/SDL3_ttf/SDL_ttf.h"
#include "../../vendored/SDL/src_mixer/include/SDL3_mixer/SDL_mixer.h"
#include "SDL/SDLRendering.hpp"
#include "openGL/GLRendering.hpp"
#include "openGL/vertex.hpp"
#include "openGL/shader.hpp"
#include "openGL/renderer.hpp"

#include <unordered_map>
#include <vector>
#include <string>
#include <map>

namespace secret {
namespace rend {

class RenderSys {
public:

  enum class CallType {

    // DEPRECATED

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

    GL_TESTTRIANGLE,
    GL_TRIANGLE,

    // NEW CALLS   

    GENERAL_VERTEX_RENDER


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
  struct GeometryDataOLD {
    SDL_Vertex* verticies;
    int numVerticies;
    int* indices;
    int numIndices;
    SDL_FPoint* points;
    int numPoints;
  };
  // all of the above will be depracted data types
  struct GeometryData {
    VertexArray va;
    IndexBuffer ib;
    Shader shader;
  };

  struct RenderCall {
    CallType type; 
    PositionalData PD;
    SizeData SD;
    RenderingData RD;
    GeometryDataOLD GDOLD;
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
