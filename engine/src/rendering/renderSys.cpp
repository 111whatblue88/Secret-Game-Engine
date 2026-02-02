#include "renderSys.hpp"
#include "../elogine.hpp"
#include "../../vendored/SDL/src_image/include/SDL3_image/SDL_image.h"

#include <SDL3/SDL_error.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_rect.h>
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <SDL3/SDL_render.h>
#include <SDL3_image/SDL_image.h>
#include <iterator>
#include <sys/types.h>

namespace engine {
namespace render {

  RenderSys::RenderSys(std::string windowName, const int width, const int height) {
    
    if (!SDL_WasInit(SDL_INIT_VIDEO)) {
      if (!SDL_Init(SDL_INIT_VIDEO)) {
        elogine::terminal::Output::log(
            elogine::terminal::Output::colorString(
              "SDL init error", 
              elogine::terminal::Output::Color::red
            ),
            elogine::terminal::Output::LogLevel::normal
        );
      } 
    }

    m_window = SDL_CreateWindow(windowName.c_str(), width, height, 0);
    if (!m_window) {
        elogine::terminal::Output::log(
            elogine::terminal::Output::colorString(
              "window creation error", 
              elogine::terminal::Output::Color::red
            ),
            elogine::terminal::Output::LogLevel::error
        );
    }
    m_renderer = SDL_CreateRenderer(m_window, NULL);
    if (!m_renderer) {
        elogine::terminal::Output::log(
            elogine::terminal::Output::colorString(
              "rendere rcreation error", 
              elogine::terminal::Output::Color::red
            ),
            elogine::terminal::Output::LogLevel::error
        );
    }

  }

  SDL_Texture* RenderSys::textureFromFont(core::Elogine& engine, ecs::TextRenderer textRenderer) {

    TTF_Font* font = TTF_OpenFont(textRenderer.fontFileLocation.c_str(), textRenderer.size);
    if (!font) {

    }
    SDL_Surface* surface = TTF_RenderText_Solid(
        font, 
        textRenderer.text.c_str(), 
        0,
        textRenderer.textFG
    );
    if (!surface) {

    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(engine.renderSys.m_renderer, surface);
    if (!texture) {

    }
    std::cout << SDL_GetError() << "\n";
    return texture;

  }
  RenderSys::~RenderSys() {
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
  }

  SDL_Texture* RenderSys::textureFromImage(core::Elogine &engine, std::string imgLocation) {
    SDL_Texture* texture = IMG_LoadTexture(engine.renderSys.m_renderer, imgLocation.c_str());
    if (!texture) {
      elogine::terminal::Output::log(
          elogine::terminal::Output::colorString(
            "error loading image", 
            elogine::terminal::Output::Color::red
          ),
          elogine::terminal::Output::LogLevel::error
      );
      std::cout << SDL_GetError() << "\n";
      elogine::terminal::Output::log(
          "loading fallback...",
          elogine::terminal::Output::LogLevel::error
      );
      SDL_Texture* texture = IMG_LoadTexture(
          engine.renderSys.m_renderer, 
          "../engine/assets/fallbacks/textures/default.png");
      if (!texture) {
        elogine::terminal::Output::log(
            elogine::terminal::Output::colorString(
              "fallback failed to load!", 
              elogine::terminal::Output::Color::red
            ),
            elogine::terminal::Output::LogLevel::error
        );
        std::cout << SDL_GetError() << "\n";
      }

    }
    return texture;

  }

  bool RenderSys::render(core::Elogine& engine) {

    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);

    std::sort(engine.entitySys.validEntities.begin(), engine.entitySys.validEntities.end(),
      [&](uint32_t a, uint32_t b) {
    
      if (!engine.entitySys.rendererComponent.has(a)) {
        return b > a;
      } else if (!engine.entitySys.rendererComponent.has(b)) {
        return a > b;
      } else if (
        !engine.entitySys.rendererComponent.has(b) && !engine.entitySys.rendererComponent.has(a)
      ) {
        return a == b;
      }

      ecs::Renderer& Ent1 = engine.entitySys.rendererComponent.get(a);
      ecs::Renderer& Ent2 = engine.entitySys.rendererComponent.get(b);

      if (Ent1.layer > Ent2.layer) {
        return a > b;
      } else {
        return b > a;
      }

    }); 
    // for image rendering
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
    // for text rendering
    for (size_t i = 0; i < engine.entitySys.validEntities.size(); i++) {
        if (engine.entitySys.textRendererComponent.has(engine.entitySys.validEntities[i])) {


          ecs::TextRenderer textRenderComp = engine.entitySys.textRendererComponent.get(engine.entitySys.validEntities[i]);
          ecs::Transform transformComp = engine.entitySys.transformComponent.get(engine.entitySys.validEntities[i]);
          SDL_FRect destination = {
            (float)transformComp.position.x, 
            (float)transformComp.position.y, 
            (float)transformComp.width, 
            (float)transformComp.height
          };
          SDL_RenderTexture(
              m_renderer, 
              textRenderComp.texture, 
              NULL, 
              &destination
          );
        }
    }    
    // for SDL square rendering
    for (size_t i = 0; i < engine.entitySys.validEntities.size(); i++) {
        if (engine.entitySys.sdlSquareComponent.has(engine.entitySys.validEntities[i])) {
          ecs::SDLSquare squareComp = engine.entitySys.sdlSquareComponent.get(engine.entitySys.validEntities[i]);
          ecs::Transform transformComp = engine.entitySys.transformComponent.get(engine.entitySys.validEntities[i]);
          SDL_FRect destination = {
            transformComp.position.x += squareComp.offset.x, 
            transformComp.position.y += squareComp.offset.y, 
            transformComp.width += squareComp.offset.w, 
            transformComp.height += squareComp.offset.h, 
          };
          SDL_SetRenderDrawColor(m_renderer, 
              squareComp.color.r, 
              squareComp.color.g, 
              squareComp.color.b, 
              squareComp.color.a
          );
          SDL_RenderFillRect(m_renderer, &destination); 
        }
    }    
    // for SDL square w outline rendering
    for (size_t i = 0; i < engine.entitySys.validEntities.size(); i++) {
        if (engine.entitySys.sdlSquareOutlineComponent.has(engine.entitySys.validEntities[i])) {
          ecs::SDLSquareOutline squareComp = engine.entitySys.sdlSquareOutlineComponent.get(engine.entitySys.validEntities[i]);
          ecs::Transform transformComp = engine.entitySys.transformComponent.get(engine.entitySys.validEntities[i]);
          SDL_FRect destination = {
            transformComp.position.x += squareComp.offset.x, 
            transformComp.position.y += squareComp.offset.y, 
            transformComp.width += squareComp.offset.w, 
            transformComp.height += squareComp.offset.h, 
          };
          SDL_SetRenderDrawColor(m_renderer, 
              squareComp.color.r, 
              squareComp.color.g, 
              squareComp.color.b, 
              squareComp.color.a
          );
          SDL_RenderRect(m_renderer, &destination); 
        }
    }    


    SDL_RenderPresent(m_renderer);

    return true;
  }




}
}



