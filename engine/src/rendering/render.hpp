#ifndef _RENDER_HPP
#define _RENDER_HPP

#include <string>
#include <SDL3/SDL.h>

namespace elo {
    struct RenderContext {

        RenderContext(std::string inName, float inWidth, float inHeight);
        ~RenderContext();

        const float M_WINDOW_WIDTH;
        const float M_WINDOW_HEIGHT;

        SDL_Window* m_window;
        SDL_Renderer* m_renderer;

    };
}


#endif
