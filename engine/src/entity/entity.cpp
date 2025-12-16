#include "entity.hpp"
#include "../elogine.hpp"

#include <iostream>
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_render.h>



void elo::RenderingComp::changeImage(const elo::elogine &engine, const std::string imagePath) {
  m_texture = IMG_LoadTexture(engine.m_mainContext.m_renderer, imagePath.c_str());
  if (!m_texture) {
    TermOutput::SDLError("error creating image texture");
  }
  //TODO: add in fallback

}
void elo::RenderingComp::render(SDL_Renderer* renderer) {
  SDL_RenderTexture(renderer, m_texture, NULL, &m_imageLocation);
}

elo::RenderingComp::~RenderingComp() {SDL_DestroyTexture(m_texture);}

elo::Entity::Entity(int x, int y) {
  this->x = x;
  this->y = y;

  //disable all components
  rendEnabled=false;

}







