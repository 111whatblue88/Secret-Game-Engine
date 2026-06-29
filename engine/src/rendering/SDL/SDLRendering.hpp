#ifndef _SDLRENDERING_HPP
#define _SDLRENDERING_HPP

#include "../../general/general.hpp"
#include "../../../vendored/SDL/src/include/SDL3/SDL.h"
#include "../../../vendored/SDL/src_image/include/SDL3_image/SDL_image.h"
#include "../../../vendored/SDL/src_ttf/include/SDL3_ttf/SDL_ttf.h"

#include <unordered_map>
#include <vector>
#include <string>
#include <map>

namespace secret {
namespace rend {

class SDL {
  public: 

  bool init(int width, int height, std::string name);

  void renderClear(); 
  void renderPresent();
  void renderPresentGL();

  void setRenderColor(Color color);

  void renderPoints(SDL_FPoint* p, int c);
  void renderGeometry(SDL_Vertex* v, int numverticies, int* indecies, int numindices);

  void renderBox(Vec2 pos, float width, float height, Color color);
  void renderBoxFill(Vec2 pos, float width, float height, Color color);

  void renderCircle(Vec2 pos, float radius, Color color);
  void renderCircleFill(Vec2 pos, float radius, Color color);

  void renderLine(Vec2 pos1, Vec2 pos2, Color color);

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

}
}

#endif
