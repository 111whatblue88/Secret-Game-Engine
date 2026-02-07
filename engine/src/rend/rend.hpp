#ifndef _REND_HPP
#define _REND_HPP

#include "../general/general.hpp"

#include <SDL3/SDL_rect.h>
#include <vector>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>

namespace elo {
namespace rend {


class Renderer {
  public: 

  bool init(int width, int height, std::string name);

  void renderClear(); 
  void renderPresent();

  void setRenderColor(Color color);

  void renderBox(Vector2 pos, float width, float height, Color color);
  void renderBoxFill(Vector2 pos, float width, float height, Color color);
  
  SDL_Texture* textureFromImage(std::string location);
 
  void renderTexture(SDL_Texture* texture, SDL_FRect uv, int layer, SDL_FRect location);
  void renderTexture(SDL_Texture* texture, int layer, SDL_FRect location);

  private:

  SDL_Renderer* m_renderer;
  SDL_Window* m_window;

};
class RenderSys {
public:

  enum class CallType {
    BOXFILL,
    BOX,
    SETDRAWCOLOR,
    TEXTURE,
    FULLTEXTURE,
  };

  struct RenderCall {
    CallType type; 
    elo::Vector2 pos;
    float width;
    float height;
    Color color;

    SDL_Texture* texture;
    SDL_FRect uv;
    int layer;
  };


  static Renderer m_renderer;

  static bool render();

  static std::vector<RenderCall> CallList;

};

#endif

}
}
