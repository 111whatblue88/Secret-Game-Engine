
#include "elogine.hpp"

#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_timer.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <memory>
#include <string>
#include <format>
#include <algorithm>

namespace engine {
namespace core {

  Elogine::Elogine(std::string windowName, int width, int height) 
    :m_WINDOWWIDTH(width), m_WINDOWHEIGHT(height), m_targetFPS(60), renderSys(windowName, width, height), running(true) {
    //log the engine starting
    if (!SDL_WasInit(SDL_INIT_VIDEO)) {
      if (SDL_Init(SDL_INIT_VIDEO)) {
        //log error and exit
      } 
    }
    if (TTF_WasInit() == 0) {
      if (!TTF_Init()) {
        //log error and exit
      }
    }

  }

  Elogine::~Elogine() {
    SDL_Quit();
    TTF_Quit();
    //log the engine quitting
  }

  bool Elogine::run() {

    SDL_Event testevent;

    uint32_t lastFrametime;

    //main loop
    while (running) {

      Uint64 currentFrametime = SDL_GetTicks();
      m_deltaTime = (currentFrametime-lastFrametime)/1000.0f;
      lastFrametime = currentFrametime; 

      //temp input 
      while (SDL_PollEvent(&testevent)) {
        if (testevent.type == SDL_EVENT_QUIT) {
          running = false;
        }
      }
      //input
      update();
      renderSys.render(*this);


      Uint32 frametime = SDL_GetTicks() - currentFrametime;
      if (frametime<1000/m_targetFPS) {
        SDL_Delay((1000/m_targetFPS)-frametime);
      }

    } 

    return true;
  }

  void Elogine::earlyExit() {
    running = false;
    //log early exit
  }

  int Elogine::targetFPS() {return m_targetFPS;}
  void Elogine::setTargetFPS(int FPS) {m_targetFPS=FPS;}
  float Elogine::deltaTime() {return m_deltaTime;}

  bool Elogine::update() {
    
    Update();

    return true;
  }







}













} // namespace elo
