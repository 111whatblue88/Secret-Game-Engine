#ifndef _RENDER_HPP
#define _RENDER_HPP

#include <string>
#include <SDL3/SDL.h>

namespace elo {
    struct RenderContext {

        RenderContext(std::string inName, float inWidth, float inHeight, int inTargetFPS);
        ~RenderContext();

        const float M_WINDOW_WIDTH;
        const float M_WINDOW_HEIGHT;

        int targetFPS;

        SDL_Window* m_window;
        SDL_Renderer* m_renderer;

    };
}


#endif