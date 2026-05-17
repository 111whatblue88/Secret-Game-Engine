#ifndef _REND_HPP
#define _REND_HPP

#include "../general/general.hpp"
#include "../../vendored/SDL/src/include/SDL3/SDL.h"
#include "../../vendored/SDL/src_image/include/SDL3_image/SDL_image.h"
#include "../../vendored/SDL/src_ttf/include/SDL3_ttf/SDL_ttf.h"

#include <unordered_map>
#include <vector>
#include <string>
#include <map>

namespace huge {
namespace rend {


class Renderer {
  public: 

  bool init(int width, int height, std::string name);

  void renderClear(); 
  void renderPresent();

  void setRenderColor(Color color);

  void renderPoints(SDL_FPoint* p, int c);
  void renderGeometry(SDL_Vertex* v, int numverticies, int* indecies, int numindices);

  void renderBox(Vector2 pos, float width, float height, Color color);
  void renderBoxFill(Vector2 pos, float width, float height, Color color);

  void renderCircle(Vector2 pos, float radius, Color color);
  void renderCircleFill(Vector2 pos, float radius, Color color);

  void renderLine(Vector2 pos1, Vector2 pos2, Color color);

  SDL_Texture* textureFromImage(std::string location);
  SDL_Texture* textureFromFont(std::string location, int fontSize, Color color, std::string text);
  SDL_Texture* textureFromFont(TTF_Font* font, Color color, std::string text);

  TTF_Font* createFont(std::string location, int fontSize);

  void renderTexture(SDL_Texture* texture, SDL_FRect uv, int layer, SDL_FRect location);
  void renderTextureFull(SDL_Texture* texture, int layer, SDL_FRect location);

  bool wasInit();

  private:

  SDL_Renderer* m_renderer;
  SDL_Window* m_window;

};
class RenderSys {
public:

  enum class CallType {
    RBOXFILL,
    RBOX,
    RCIRCLE,
    RCIRCLEFILL,
    RLINE,
    SETDRAWCOLOR,
    RTEXTURE,
    RFULLTEXTURE,
    RGEOMETRY,
    RPOINTS,
  };

  struct PositionalData {
    huge::Vector2 pos;
    Vector2 pos2;
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


  static Renderer m_renderer;

  static bool render();

  static std::vector<RenderCall> CallList;

};

#endif

}
}
