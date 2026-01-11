#ifndef _RENDERSYS_HPP
#define _RENDERSYS_HPP

#include "../../vendored/SDL/src/include/SDL3/SDL.h"
#include <string>

namespace engine {
namespace core {
class Elogine;
}
namespace render {

  class RenderSys {
  friend class core::Elogine;
  public:
    
    static SDL_Texture* textureFromImage(core::Elogine& engine, std::string imgLocation);

  private:

    RenderSys(std::string windowName, const int width, const int height);
    ~RenderSys();

    SDL_Window* m_window;
    SDL_Renderer* m_renderer;

    bool render(core::Elogine& engine);

  };

}
}

#endif







