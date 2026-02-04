#include "../ELOgine.hpp"
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>

#include <cstddef>
#include <iostream>
#include <string>

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


Renderer RenderSys::m_renderer = Renderer();

std::vector<RenderSys::RenderCall> RenderSys::CallList = std::vector<RenderSys::RenderCall>();

bool RenderSys::render() {

  m_renderer.setRenderColor(Color{0,0,0});
  m_renderer.renderClear();

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
    }
  }  
  CallList.clear();


  m_renderer.renderPresent();
  return true;  
};


}

}


