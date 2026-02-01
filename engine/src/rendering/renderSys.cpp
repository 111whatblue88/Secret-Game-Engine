#include "renderSys.hpp"
#include "../elogine.hpp"
#include "../../vendored/SDL/src_image/include/SDL3_image/SDL_image.h"

#include <iostream>
#include <SDL3/SDL_render.h>
#include <SDL3_image/SDL_image.h>
#include <iterator>

namespace engine {
namespace render {

  RenderSys::RenderSys(std::string windowName, const int width, const int height) {
    
    if (!SDL_WasInit(SDL_INIT_VIDEO)) {
      if (SDL_Init(SDL_INIT_VIDEO)) {
        //log error and exit
      } 
    }

    m_window = SDL_CreateWindow(windowName.c_str(), width, height, 0);
    if (!m_window) {
      //log window and crash
    }
    m_renderer = SDL_CreateRenderer(m_window, NULL);
    if (!m_renderer) {
      //log renderer and crash
    }

  }

  RenderSys::~RenderSys() {
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
  }

  SDL_Texture* RenderSys::textureFromImage(core::Elogine &engine, std::string imgLocation) {
    SDL_Texture* texture = IMG_LoadTexture(engine.renderSys.m_renderer, imgLocation.c_str());
    if (!texture) {
      std::cout << "testerro";
      //load fallback
      std::cout << SDL_GetError() << "\n";
    }
    return texture;

  }

  bool RenderSys::render(core::Elogine& engine) {

    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);

    for (size_t i = 0; i < engine.entitySys.validEntities.size(); i++) {

        if (engine.entitySys.rendererComponent.has(engine.entitySys.validEntities[i])) {
          ecs::Renderer renderComp = engine.entitySys.rendererComponent.get(engine.entitySys.validEntities[i]);
          ecs::Transform transformComp = engine.entitySys.transformComponent.get(engine.entitySys.validEntities[i]);
          SDL_FRect destination = {
            (float)transformComp.position.x, 
            (float)transformComp.position.y, 
            (float)transformComp.width, 
            (float)transformComp.height
          };
          SDL_RenderTexture(
              m_renderer, 
              renderComp.texture, 
              &renderComp.uv, 
              &destination
          );
        }



    }    


    SDL_RenderPresent(m_renderer);

    return true;
  }



}
}



