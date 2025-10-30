
#include "elogine.hpp"

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

namespace elo {

    elogine::elogine(std::string name, float width, float height)
        : m_quit(false), m_mainContext(name, width, height)
    {

        if (SDL_WasInit(SDL_INIT_VIDEO) == SDL_INIT_STATUS_UNINITIALIZED) {
            if (!SDL_Init(SDL_INIT_VIDEO)) {

            }
        }

        if (TTF_WasInit() <= 0) {
            if (!TTF_Init()) {

            }
        }

    }

    elogine::~elogine() {
        SDL_Quit();
        TTF_Quit();
    }

    bool elogine::run() {

        SDL_Event event;

        while (!m_quit) {

            // TODO: add in other systems for input and rendering. And a frame system

            //input

            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_EVENT_QUIT) {
                    m_quit = true;
                }
            } 

            //render

            SDL_SetRenderDrawColor(m_mainContext.m_renderer, 0, 0, 0, 255);
            SDL_RenderClear(m_mainContext.m_renderer);
        
            SDL_RenderPresent(m_mainContext.m_renderer);            

        }


        return true;
        
    }


}
