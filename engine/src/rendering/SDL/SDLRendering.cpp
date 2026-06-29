#include "../../secret.hpp"
#include "../../../vendored/SDL/src/include/SDL3/SDL.h"
#include "../../../vendored/SDL/src_ttf/include/SDL3_ttf/SDL_ttf.h"
#include "SDLRendering.hpp"

#include <SDL3/SDL_init.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <format>
#include <cstddef>
#include <cstdint>
#include <string>
#include <sys/types.h>
#include <unordered_map>

namespace secret {
namespace rend {

using namespace console;

bool SDL::init(int width, int height, std::string name) {

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  SDL_GL_SetAttribute(
    SDL_GL_CONTEXT_PROFILE_MASK,
    SDL_GL_CONTEXT_PROFILE_CORE
  );

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
  m_window = SDL_CreateWindow(name.c_str(), width, height, SDL_WINDOW_OPENGL);
  if (!m_window) {
    COutput::logCustom("FATAL ERROR", "Window creation failed", COutput::MsgColor::red);
    COutput::logSDLError();
    core::Engine::earlyExit("No window");
    return false; 
  }
  m_renderer = SDL_CreateRenderer(m_window, NULL);
  if (!m_renderer) {
    COutput::logCustom("FATAL ERROR", "Renderer creation failed", COutput::MsgColor::red);
    COutput::logSDLError();

    core::Engine::earlyExit("No renderer");
    return false;
  }

  // GL context setup 
  openGL::GLContext = SDL_GL_CreateContext(m_window);

  if (core::Engine::options.renderingAPI == core::RenderingAPIs::openGL) {
    SDL_GL_MakeCurrent(m_window, openGL::GLContext);
  }

  return true;
}

bool SDL::wasInit() {
if (!m_renderer && !m_window) {
  return false;
} else {
  return true;
}
}

void SDL::renderClear() {
  SDL_RenderClear(m_renderer);
}
void SDL::setRenderColor(Color color) {
  SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, 255); 
}
void SDL::renderPresent() {
  SDL_RenderPresent(m_renderer);
}
void SDL::renderPresentGL() {
  SDL_GL_SwapWindow(m_window);
}
void SDL::renderGeometry(SDL_Vertex* v, int numverticies, int* indices, int numindices) {
  SDL_RenderGeometry(m_renderer, NULL, v, numverticies, indices, numindices);
}
void SDL::renderPoints(SDL_FPoint* p, int c) {
  SDL_RenderPoints(m_renderer, p, c);
}
void SDL::renderBox(Vec2 pos, float width, float height, Color color) {
  setRenderColor(color);
SDL_FRect rect = {pos.x, pos.y, width, height};
  SDL_RenderRect(m_renderer, &rect);
}
void SDL::renderBoxFill(Vec2 pos, float width, float height, Color color) {
  setRenderColor(color);
SDL_FRect rect = {pos.x, pos.y, width, height};
  SDL_RenderFillRect(m_renderer, &rect);
}
void SDL::renderLine(Vec2 pos1, Vec2 pos2, Color color) {
  setRenderColor(color);
  SDL_RenderLine(m_renderer, pos1.x, pos1.y, pos2.x, pos2.y);
}
void SDL::renderCircle(Vec2 pos, float radius, Color color) {
  setRenderColor(color);

  const int32_t diameter = (radius * 2);

  int32_t x = (radius - 1);
  int32_t y = 0;
  int32_t tx = 1;
  int32_t ty = 1;
  int32_t error = (tx - diameter);
  
  std::vector<SDL_FPoint> points;

  while (x >= y)
  {

    points.push_back({pos.x + x, pos.y - y});
    points.push_back({pos.x + x, pos.y + y});
    points.push_back({pos.x - x, pos.y - y});
    points.push_back({pos.x - x, pos.y + y});
    points.push_back({pos.x + y, pos.y - x});
    points.push_back({pos.x + y, pos.y + x});
    points.push_back({pos.x - y, pos.y - x});
    points.push_back({pos.x - y, pos.y + x});

    if (error <= 0)
    {
        ++y;
        error += ty;
        ty += 2;
    }

    if (error > 0)
    {
        --x;
        tx += 2;
        error += (tx - diameter);
    }
  }
  this->renderPoints(points.data(), int(points.size()));

}

void SDL::renderCircleFill(Vec2 pos, float radius, Color color) {
setRenderColor(color);

int offsetx, offsety, d;
int status;

offsetx = 0;
offsety = radius;
d = radius -1;
status = 0;

while (offsety >= offsetx) {

    status += SDL_RenderLine(m_renderer, pos.x - offsety, pos.y + offsetx,
                                  pos.x + offsety, pos.y + offsetx);
    status += SDL_RenderLine(m_renderer, pos.x - offsetx, pos.y + offsety,
                                  pos.x + offsetx, pos.y + offsety);
    status += SDL_RenderLine(m_renderer, pos.x - offsetx, pos.y - offsety,
                                  pos.x + offsetx, pos.y - offsety);
    status += SDL_RenderLine(m_renderer, pos.x - offsety, pos.y - offsetx,
                                  pos.x + offsety, pos.y - offsetx);

    if (status < 0) {
        status = -1;
        break;
    }

    if (d >= 2*offsetx) {
        d -= 2*offsetx + 1;
        offsetx +=1;
    }
    else if (d < 2 * (radius - offsety)) {
        d += 2 * offsety - 1;
        offsety -= 1;
    }
    else {
        d += 2 * (offsety - offsetx - 1);
        offsety -= 1;
        offsetx += 1;
    }
}
}

SDL_Texture* SDL::textureFromImage(std::string location) {
SDL_Texture* texture;
texture = IMG_LoadTexture(m_renderer, location.c_str());
if (!texture) {

  COutput::logError(std::format("loading texture failed, given file location was \"{}\", loading fallback", location));
  COutput::logSDLError();

  filesystem::locateToEngineRoot();
  texture = IMG_LoadTexture(
      m_renderer, 
      "engine/assets/fallbacks/textures/default.png"
  );
  if (!texture) {
    COutput::logError("loading fallback texture failed!");
    COutput::logSDLError();
  } else {
    COutput::logCustom("ENGINE","loaded fallback texture successfully");
  }
}
return texture;
}

SDL_Texture* SDL::textureFromFont(std::string fontLocation, int fontSize, Color color, std::string text) {

if (fontLocation == "default") {
  filesystem::locateToEngineRoot();
  TTF_Font* font = TTF_OpenFont("engine/assets/fallbacks/fonts/jetbrains.ttf", fontSize);
  
  if (!font) {
    COutput::logError("loading default font failed!");
    COutput::logSDLError();
  }

  SDL_Surface* surface = TTF_RenderText_Solid(
      font,
      text.c_str(), 
      0, 
      SDL_Color{Uint8(color.r),Uint8(color.g),Uint8(color.b), 255
  });
  return SDL_CreateTextureFromSurface(m_renderer, surface);
}

TTF_Font* font = TTF_OpenFont(fontLocation.c_str(), fontSize);
if (!font) {
  COutput::logError(std::format("loading font failed, given file location was \"{}\", loading fallback", fontLocation));
  COutput::logSDLError();
  filesystem::locateToEngineRoot();
  font = TTF_OpenFont("engine/assets/fallbacks/fonts/jetbrains.ttf", fontSize);
  if (!font) {
    COutput::logError("loading fallback font failed!");
    COutput::logSDLError();
  } else {
    COutput::logCustom("ENGINE","loaded fallback font successfully");
  }
}

SDL_Surface* surface = TTF_RenderText_Solid(
    font,
    text.c_str(), 
    0, 
    SDL_Color{Uint8(color.r),Uint8(color.g),Uint8(color.b), 255
});

return SDL_CreateTextureFromSurface(m_renderer, surface);

}
SDL_Texture* SDL::textureFromFont(TTF_Font* font, Color color, std::string text) {

SDL_Surface* surface = TTF_RenderText_Solid(
    font,
    text.c_str(), 
    0, 
    SDL_Color{Uint8(color.r),Uint8(color.g),Uint8(color.b), 255
});

return SDL_CreateTextureFromSurface(m_renderer, surface);

}
TTF_Font* SDL::createFont(std::string location, int fontSize) {

if (location == "default") {
  filesystem::locateToEngineRoot();
  TTF_Font* font = TTF_OpenFont("engine/assets/fallbacks/fonts/jetbrains.ttf", fontSize);
  
  if (!font) {
    COutput::logError("loading default font failed!");
    COutput::logSDLError();
  }

  return font;
}

TTF_Font* font = TTF_OpenFont(location.c_str(), fontSize);
if (!font) {
  COutput::logError(std::format("loading font failed, given file location was \"{}\", loading fallback", location));
  COutput::logSDLError();
  filesystem::locateToEngineRoot();
  font = TTF_OpenFont("engine/assets/fallbacks/fonts/jetbrains.ttf", fontSize);
  if (!font) {
    COutput::logError("loading fallback font failed!");
    COutput::logSDLError();
  } else {
    COutput::logCustom("ENGINE","loaded fallback font successfully");
  }
}
return font;
}



void SDL::renderTexture(SDL_Texture* texture, SDL_FRect uv, int layer, SDL_FRect location) {
SDL_RenderTexture(
  m_renderer, 
  texture, 
  &uv, 
  &location
);
}
void SDL::renderTextureFull(SDL_Texture* texture, int layer, SDL_FRect location) {
SDL_RenderTexture(
  m_renderer, 
  texture, 
  NULL,
  &location
);
}

}
}
