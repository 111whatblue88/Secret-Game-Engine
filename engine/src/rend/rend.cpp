#include "../ELOgine.hpp"
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>

#include <cstddef>
#include <iostream>
#include <string>
#include <unordered_map>

namespace elo {
namespace rend {

bool Renderer::init(int width, int height, std::string name) {
  if (!SDL_WasInit(SDL_INIT_VIDEO)) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
      return false;
    } 
  }
  if (TTF_WasInit() == 0) {
    if (!TTF_Init()) {
      return false;
    }
  }
  m_window = SDL_CreateWindow(name.c_str(), width, height, 0);
  if (!m_window) {
    return false; 
  }
  m_renderer = SDL_CreateRenderer(m_window, NULL);
  if (!m_renderer) {
    return false;
  }

  return true;
}
 
void Renderer::renderClear() {
  SDL_RenderClear(m_renderer);
}
void Renderer::setRenderColor(Color color) {
  SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, 255); 
}
void Renderer::renderPresent() {
  SDL_RenderPresent(m_renderer);
}
void Renderer::renderBox(Vector2 pos, float width, float height, Color color) {
  setRenderColor(color);
  SDL_FRect rect = {pos.x, pos.y, width, height};
  SDL_RenderRect(m_renderer, &rect);
}
void Renderer::renderBoxFill(Vector2 pos, float width, float height, Color color) {
  setRenderColor(color);
  SDL_FRect rect = {pos.x, pos.y, width, height};
  SDL_RenderFillRect(m_renderer, &rect);
}
SDL_Texture* Renderer::textureFromImage(std::string location) {
  SDL_Texture* texture = IMG_LoadTexture(m_renderer, location.c_str());
  if (!texture) {
    SDL_Texture* texture = IMG_LoadTexture(
        m_renderer, 
        "../engine/assets/fallbacks/textures/default.png");
    if (!texture) {
    }

  }
  return texture;
}

void Renderer::renderTexture(SDL_Texture* texture, SDL_FRect uv, int layer, SDL_FRect location) {
  SDL_RenderTexture(
    m_renderer, 
    texture, 
    &uv, 
    &location
  );
}
void Renderer::renderTexture(SDL_Texture* texture, int layer, SDL_FRect location) {
  SDL_RenderTexture(
    m_renderer, 
    texture, 
    NULL,
    &location
  );
}

Renderer RenderSys::m_renderer = Renderer();

std::vector<RenderSys::RenderCall> RenderSys::CallList = std::vector<RenderSys::RenderCall>();

bool RenderSys::render() {

  m_renderer.setRenderColor(Color{0,0,0});
  m_renderer.renderClear();

  // render components components
  std::vector<uint32_t> entityList = ecs::EntitySys::getEntityList();
  for (size_t i = 0; i < entityList.size(); i++) {
    ecs::Transform& TComp = ecs::TransformComponent::get(entityList[i]);

    if (ecs::ImgRendererComp::has(entityList[i])) {
      ecs::ImgRenderer& IRComp = ecs::ImgRendererComp::get(entityList[i]);
      if (SDL_RectEmptyFloat(&IRComp.uv)) {
        CallList.push_back(RenderCall{
          CallType::TEXTURE,
          TComp.pos,
          TComp.width,
          TComp.width,
          Color{0,0,0},
          IRComp.texture,
          IRComp.uv,
          IRComp.layer
        }); 
      } else {
        CallList.push_back(RenderCall{
          CallType::FULLTEXTURE,
          TComp.pos,
          TComp.width,
          TComp.width,
          Color{0,0,0},
          IRComp.texture,
          IRComp.uv,
          IRComp.layer
        }); 
      }
    }
    
    if (ecs::PrimitiveRendererComponent::has(entityList[i])) {
      ecs::PrimitiveRenderer& PRComp = ecs::PrimitiveRendererComponent::get(entityList[i]);
      switch (PRComp.type) {
        case ecs::PrimitiveRenderer::PrimitiveType::square: {
          CallList.push_back(RenderCall{
            CallType::BOX,
            TComp.pos,
            TComp.width,
            TComp.height,
            PRComp.color
          });
          break;
        }
        case ecs::PrimitiveRenderer::PrimitiveType::sqaureFill: {
          CallList.push_back(RenderCall{
            CallType::BOXFILL,
            TComp.pos,
            TComp.width,
            TComp.height,
            PRComp.color
          });
          break;
        }
      }
    }
  } 

  // proccess callbacks
  for (size_t i = 0; i < CallList.size(); i++) {
    
    switch (CallList[i].type) {
      
      case CallType::BOX:
        m_renderer.renderBox(
          CallList[i].pos, 
          CallList[i].width, 
          CallList[i].height, 
          CallList[i].color
        );
        break;
      case CallType::BOXFILL:
        m_renderer.renderBoxFill(
          CallList[i].pos, 
          CallList[i].width, 
          CallList[i].height, 
          CallList[i].color
        );
        break;
      case CallType::SETDRAWCOLOR:
        m_renderer.setRenderColor(CallList[i].color);
        break;
      case CallType::TEXTURE:
        m_renderer.renderTexture(
          CallList[i].texture,
          CallList[i].uv,
          CallList[i].layer,
          SDL_FRect{
            CallList[i].pos.x,
            CallList[i].pos.y,
            CallList[i].width,
            CallList[i].height
          }
        );
      break;
      case CallType::FULLTEXTURE:
        m_renderer.renderTexture(
          CallList[i].texture,
          CallList[i].layer,
          SDL_FRect{
            CallList[i].pos.x,
            CallList[i].pos.y,
            CallList[i].width,
            CallList[i].height
          }
        );
      break;

    }
  }  
  CallList.clear();

  m_renderer.renderPresent();
  return true;  
};


}

}


