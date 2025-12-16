
#include "../elogine.hpp"

#include <SDL3/SDL.h>
#include <SDL3/SDL_error.h>
#include <cinttypes>
#include <string>
#include <format>
#include <print>

namespace elo {

RenderContext::RenderContext(std::string inName, float inWidth, float inHeight)
    : M_WINDOW_WIDTH(inWidth), M_WINDOW_HEIGHT(inHeight){

  auto SDLError = [](const std::string& ErrMsg) {
    TermOutput::outputStyle(
        TermOutput::colorString(
          std::format("{}: {}", ErrMsg, SDL_GetError()),
          TermOutput::Color::red), 
        TermOutput::StyleType::error);
    throw std::runtime_error(ErrMsg);
  };

  if (SDL_WasInit(SDL_INIT_VIDEO) == SDL_INIT_STATUS_UNINITIALIZED) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
      SDLError("Error initializing SDL");
    }
  }

  m_window = SDL_CreateWindow(inName.c_str(), M_WINDOW_WIDTH, M_WINDOW_HEIGHT, 0);
  if (!m_window) {
    SDLError("Error creating the window");
  }
  m_renderer = SDL_CreateRenderer(m_window, NULL);
  if (!m_renderer) {
    SDLError("Error creating the renderer");
  }
}

RenderContext::~RenderContext() {

  SDL_DestroyRenderer(m_renderer);
  SDL_DestroyWindow(m_window);
}

} // namespace elo
