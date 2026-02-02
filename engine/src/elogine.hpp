#ifndef _ELOGINE_HPP
#define _ELOGINE_HPP

#include "ecs/ecs.hpp"
#include "rendering/renderSys.hpp"
#include "terminal/input.hpp"
#include "terminal/output.hpp"

#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3/SDL.h>
#include <functional>


namespace engine {
namespace core {

  class Elogine {
    struct Options {
      Options();
      int m_targetFPS;  
    };
    public:

    Options engineOptions;

    Elogine(std::string windowName, int width, int height);
    ~Elogine();

    bool run();
    void earlyExit();

    std::function<void()> Update;

    float deltaTime();

    const int m_WINDOWWIDTH;
    const int m_WINDOWHEIGHT;

    render::RenderSys renderSys;
    ecs::EntitySys entitySys;

  private:

    bool running;
    float m_deltaTime;
    bool update();

  };

}
}


#endif
