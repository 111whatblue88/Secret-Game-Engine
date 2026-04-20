#include "../ELOgine.hpp"
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>

#include <cmath>
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
void Renderer::renderGeometry(SDL_Vertex* v, int numverticies, int* indices, int numindices) {
  SDL_RenderGeometry(m_renderer, NULL, v, numverticies, indices, numindices);
}
void Renderer::renderPoints(SDL_FPoint* p, int c) {
  SDL_RenderPoints(m_renderer, p, c);
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
void Renderer::renderCircle(Vector2 pos, float radius, Color color) {
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

void Renderer::renderCircleFill(Vector2 pos, float radius, Color color) {
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

SDL_Texture* Renderer::textureFromFont(std::string fontLocation, int fontSize, Color color, std::string text) {
  
  TTF_Font* font = TTF_OpenFont(fontLocation.c_str(), fontSize);
  if (!font) {
    // add logging for fallback font being loaded
    font = TTF_OpenFont("../engine/assets/fallbacks/fonts/jetbrains.ttf", fontSize);
    if (!font) {
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

void Renderer::renderTexture(SDL_Texture* texture, SDL_FRect uv, int layer, SDL_FRect location) {
  SDL_RenderTexture(
    m_renderer, 
    texture, 
    &uv, 
    &location
  );
}
void Renderer::renderTextureFull(SDL_Texture* texture, int layer, SDL_FRect location) {
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
          CallType::RTEXTURE,
          TComp.pos,
          TComp.width,
          TComp.width,
          0,
          Color{0,0,0},
          IRComp.texture,
          IRComp.uv,
          IRComp.layer
        }); 
      } else {
        CallList.push_back(RenderCall{
          CallType::RFULLTEXTURE,
          TComp.pos,
          TComp.width,
          TComp.width,
          0,
          Color{0,0,0},
          IRComp.texture,
          IRComp.uv,
          IRComp.layer
        }); 
      }
    }
   
    if (ecs::ImgRendererComp::has(entityList[i])) {
      ecs::TextRenderer& TRComp = ecs::TextRendererComp::get(entityList[i]);
        CallList.push_back(RenderCall{
          CallType::RFULLTEXTURE,
          TComp.pos,
          TComp.width,
          TComp.width,
          0,
          Color{0,0,0},
          TRComp.texture,
          float(TRComp.layer)
        }
      ); 
    }

    if (ecs::PrimitiveRendererComponent::has(entityList[i])) {
      ecs::PrimitiveRenderer& PRComp = ecs::PrimitiveRendererComponent::get(entityList[i]);
      switch (PRComp.type) {
        case ecs::PrimitiveRenderer::PrimitiveType::square: {
          CallList.push_back(RenderCall{
            CallType::RBOX,
            TComp.pos,
            TComp.width,
            TComp.height,
            0,
            PRComp.color
          });
          break;
        }
        case ecs::PrimitiveRenderer::PrimitiveType::sqaureFill: {
          CallList.push_back(RenderCall{
            CallType::RBOXFILL,
            TComp.pos,
            TComp.width,
            TComp.height,
            0,
            PRComp.color
          });
          break;
        }
        case ecs::PrimitiveRenderer::PrimitiveType::circle: {
          CallList.push_back(RenderCall{
            CallType::RCIRCLE,
            TComp.pos,
            0,
            0,
            TComp.radius,
            PRComp.color,
          });
          break;
        }
        case ecs::PrimitiveRenderer::PrimitiveType::circleFill: {
          CallList.push_back(RenderCall{
            CallType::RCIRCLEFILL,
            TComp.pos,
            0,
            0,
            TComp.radius,
            PRComp.color,
          });
          break;
        }
      }
    }
  } 

  // proccess callbacks
  for (size_t i = 0; i < CallList.size(); i++) {
    
    switch (CallList[i].type) {
      
      case CallType::RBOX:
        m_renderer.renderBox(
          CallList[i].pos, 
          CallList[i].width, 
          CallList[i].height, 
          CallList[i].color
        );
        break;
      case CallType::RBOXFILL:
        m_renderer.renderBoxFill(
          CallList[i].pos, 
          CallList[i].width, 
          CallList[i].height, 
          CallList[i].color
        );
        break;
      case CallType::RCIRCLE:
        m_renderer.renderCircle(
            CallList[i].pos,
            CallList[i].radius,
            CallList[i].color
        );
        break;
      case CallType::RCIRCLEFILL:
        m_renderer.renderCircleFill(
            CallList[i].pos,
            CallList[i].radius,
            CallList[i].color
        );
        break;
      case CallType::SETDRAWCOLOR:
        m_renderer.setRenderColor(CallList[i].color);
        break;
      case CallType::RTEXTURE:
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
      case CallType::RFULLTEXTURE:
        m_renderer.renderTextureFull(
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
      case CallType::RGEOMETRY:
        m_renderer.renderGeometry(
          CallList[i].verticies, 
          CallList[i].numVerticies, 
          CallList[i].indices, 
          CallList[i].numIndices
      );
      case CallType::RPOINTS:
        m_renderer.renderPoints(
          CallList[i].points,
          CallList[i].numPoints
      );
    }
  }  
  CallList.clear();

  m_renderer.renderPresent();
  return true;  
};


}

}


