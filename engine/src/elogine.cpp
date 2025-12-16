
#include "elogine.hpp"
#include "entity/entity.hpp"

#include <SDL3/SDL.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_timer.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <memory>
#include <string>
#include <format>

namespace elo {

elogine::elogine(std::string name, float width, float height)
    : m_quit(false), m_mainContext(name, width, height) {

  if (SDL_WasInit(SDL_INIT_VIDEO) == SDL_INIT_STATUS_UNINITIALIZED) {
    if (!SDL_Init(SDL_INIT_VIDEO)){
      TermOutput::SDLError("error initializing SDL");
    }
  }

  if (TTF_WasInit() <= 0) {
    if (!TTF_Init()) {
      TermOutput::SDLError("error initializing SDL TTF");
    }
  }
}

elogine::~elogine() {
  SDL_Quit();
  TTF_Quit();
}

bool elogine::run() {

  SDL_Event event;

  Uint32 lastFrametime = SDL_GetTicks();

  while (!m_quit) {

    // TODO: lmao everything. Add systems for input, rendering, and a system to 
    // allow hooking into the engines features

    Uint64 currentFrametime = SDL_GetTicks();
    deltaTime = (currentFrametime-lastFrametime)/1000.0f;
    lastFrametime = currentFrametime; 


    // input
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_QUIT) {
        m_quit = true;
      }
    }

    // update

    // render
    render();


    Uint32 frametime = SDL_GetTicks() - currentFrametime;
    if (frametime<1000/targetFPS) {
      SDL_Delay((1000/targetFPS)-frametime);
    }

  }

  return true;
}

int elogine::TargetFPS() {return targetFPS;}
void elogine::setTargetFPS(int inTargetFPS) {targetFPS=inTargetFPS;}

void elogine::addEntity(std::unique_ptr<Entity> inEntity) {entityVector.push_back(std::move(inEntity));}

bool elogine::render() {

  SDL_SetRenderDrawColor(m_mainContext.m_renderer, 0, 0, 0, 255);
  SDL_RenderClear(m_mainContext.m_renderer);

  // go through and render any entities with renderer enabled
  for (size_t i=0; i<entityVector.size(); i++) {
    if (entityVector[i]->rendEnabled) {
      entityVector[i]->rendComp.render(m_mainContext.m_renderer);
    }
  }

  SDL_RenderPresent(m_mainContext.m_renderer);
  return true;
}

} // namespace elo
