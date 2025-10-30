
#include "../elogine.hpp"

#include <SDL3/SDL.h>

namespace elo {

    renderContext::renderContext(std::string inName, float inWidth, float inHeight)
        : M_WINDOW_WIDTH(inWidth), M_WINDOW_HEIGHT(inHeight)
    {
        // add in logging for errors when console systems are done

        if (SDL_WasInit(SDL_INIT_VIDEO) == SDL_INIT_STATUS_UNINITIALIZED) {
            if (!SDL_Init(SDL_INIT_VIDEO)) {

            }
        }

        m_window = SDL_CreateWindow(inName.c_str(), M_WINDOW_WIDTH, M_WINDOW_HEIGHT, 0);
        if (!m_window) {

        }
        m_renderer = SDL_CreateRenderer(m_window, NULL);
        if (!m_renderer) {

        }
    }

    renderContext::~renderContext() {

        SDL_DestroyRenderer(m_renderer);
        SDL_DestroyWindow(m_window);

    }

}











