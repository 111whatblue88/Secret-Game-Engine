#include "../HUGE.hpp"
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>

#include <format>
#include <SDL3_ttf/SDL_ttf.h>
#include <cstddef>
#include <cstdint>
//#include <iostream>
#include <string>
#include <sys/types.h>
#include <unordered_map>

namespace huge {
namespace rend {

using namespace console;

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
    COutput::logError("Window creation failed");
    COutput::logSDLError();
    return false; 
  }
  m_renderer = SDL_CreateRenderer(m_window, NULL);
  if (!m_renderer) {
    COutput::logError("Renderer creation failed");
    COutput::logSDLError();
    return false;
  }

  return true;
}

bool Renderer::wasInit() {
  if (!m_renderer && !m_window) {
    return false;
  } else {
    return true;
  }
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
void Renderer::renderLine(Vector2 pos1, Vector2 pos2, Color color) {
  setRenderColor(color);
  SDL_RenderLine(m_renderer, pos1.x, pos1.y, pos2.x, pos2.y);
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

    COutput::logError(std::format("loading texture failed, known file location was \"{}\", loading fallback", location));
    COutput::logSDLError();

    SDL_Texture* texture = IMG_LoadTexture(
        m_renderer, 
        "../../../engine/assets/fallbacks/textures/default.png");
        //TODO: fix below
        // the texture goes through here, but doesnt render for some reason
    if (!texture) {
      COutput::logError("loading fallback texture failed!");
      COutput::logSDLError();
    }

  }
  return texture;
}

SDL_Texture* Renderer::textureFromFont(std::string fontLocation, int fontSize, Color color, std::string text) {
  
  TTF_Font* font = TTF_OpenFont(fontLocation.c_str(), fontSize);
  if (!font) {
    COutput::logError(std::format("loading font failed, known file location was \"{}\", loading fallback", fontLocation));
    COutput::logSDLError();
    font = TTF_OpenFont("../../../engine/assets/fallbacks/fonts/jetbrains.ttf", fontSize);
    if (!font) {
      COutput::logError("loading fallback font failed!");
      COutput::logSDLError();
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
SDL_Texture* Renderer::textureFromFont(TTF_Font* font, Color color, std::string text) {

  SDL_Surface* surface = TTF_RenderText_Solid(
      font,
      text.c_str(), 
      0, 
      SDL_Color{Uint8(color.r),Uint8(color.g),Uint8(color.b), 255
  });

  return SDL_CreateTextureFromSurface(m_renderer, surface);

}
TTF_Font* Renderer::createFont(std::string location, int fontSize) {
  TTF_Font* font = TTF_OpenFont(location.c_str(), fontSize);
  if (!font) {
    COutput::logError(std::format("loading font failed, known file location was \"{}\", loading fallback", location));
    COutput::logSDLError();
    font = TTF_OpenFont("../../../engine/assets/fallbacks/fonts/jetbrains.ttf", fontSize);
    if (!font) {
      COutput::logError("loading fallback font failed!");
      COutput::logSDLError();
    }
  }
  return font;
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

using namespace ecs;

bool RenderSys::render() {

  m_renderer.setRenderColor(Color{0,0,0});
  m_renderer.renderClear();

  auto& EList = EntitySys::GetEntityList();

  for (auto E : EList) {
    
    

    // img renderer
    if (E.second.ImgRendererComp.has()) {
      for (auto IR : E.second.ImgRendererComp.getComponentList()) {
        if (IR.second.uv.x || IR.second.uv.y || IR.second.uv.w || IR.second.uv.h) {
          RenderSys::CallList.push_back(RenderSys::RenderCall{
            RenderSys::CallType::RTEXTURE,
            PositionalData{E.second.TransformComp.pos},
            SizeData{E.second.TransformComp.width, E.second.TransformComp.height},
            RenderingData{Color(0,0,0),IR.second.texture, IR.second.uv,0}
          });
        } else {
          if (!IR.second.texture) {
            std::cout << "goddamnit\n";
          }
          RenderSys::CallList.push_back(RenderSys::RenderCall{
            RenderSys::CallType::RFULLTEXTURE,
            PositionalData{E.second.TransformComp.pos},
            SizeData{E.second.TransformComp.width, E.second.TransformComp.height},
            RenderingData{Color(0,0,0),IR.second.texture, 0,0,0,0,0}
          });
        }
      }
    }

    

    // primitve renderer
    if (E.second.PrimitiveRendererComp.has()) {
      for (auto PR : E.second.PrimitiveRendererComp.getComponentList()) {
        switch (PR.second.type) {
          case ecs::PrimitiveRenderer::PrimitiveType::square: {
            RenderSys::CallList.push_back(RenderSys::RenderCall{
              RenderSys::CallType::RBOX,
              PositionalData{E.second.TransformComp.pos},
              SizeData{E.second.TransformComp.width, E.second.TransformComp.height},
              RenderingData{PR.second.color}
            });
            break;
          }
          case ecs::PrimitiveRenderer::PrimitiveType::squareFill: {
            RenderSys::CallList.push_back(RenderSys::RenderCall{
              RenderSys::CallType::RBOXFILL,
              PositionalData{E.second.TransformComp.pos},
              SizeData{E.second.TransformComp.width, E.second.TransformComp.height},
              RenderingData{PR.second.color}
            });
            break;
          }
          case ecs::PrimitiveRenderer::PrimitiveType::circle: {
            RenderSys::CallList.push_back(RenderSys::RenderCall{
              RenderSys::CallType::RCIRCLE,
              PositionalData{E.second.TransformComp.pos},
              SizeData{0,0,E.second.TransformComp.radius},
              RenderingData{PR.second.color}
            });
            break;
          }
          case ecs::PrimitiveRenderer::PrimitiveType::circleFill: {
            RenderSys::CallList.push_back(RenderSys::RenderCall{
              RenderSys::CallType::RCIRCLEFILL,
              PositionalData{E.second.TransformComp.pos},
              SizeData{0,0,E.second.TransformComp.radius},
              RenderingData{PR.second.color}
            });
            break;
          }
          case ecs::PrimitiveRenderer::PrimitiveType::line: {
            RenderSys::CallList.push_back(RenderSys::RenderCall{
              RenderSys::CallType::RLINE,
              PositionalData{E.second.TransformComp.pos, PR.second.LineTypeSecondPoint},
              SizeData{},
              RenderingData{PR.second.color}
            });
            break;
          }
        }
      }      
    }

    // Text Renderer
    if (E.second.TextRendererComp.has()) {
      for (auto TR : E.second.TextRendererComp.getComponentList()) {
        if (TR.second.inheritTransform) {
          RenderSys::CallList.push_back(RenderSys::RenderCall{
            RenderSys::CallType::RFULLTEXTURE,
            PositionalData{E.second.TransformComp.pos},
            SizeData{E.second.TransformComp.width, E.second.TransformComp.height},
            RenderingData{{0,0,0}, TR.second.texture}
          });
        } else {
          RenderSys::CallList.push_back(RenderSys::RenderCall{
            RenderSys::CallType::RFULLTEXTURE,
            PositionalData{TR.second.transform.pos},
            SizeData{TR.second.transform.width, TR.second.transform.height},
            RenderingData{{0,0,0}, TR.second.texture}
          });
        }
      }
    }


  }


  // proccess callbacks
  for (size_t i = 0; i < CallList.size(); i++) {
    
    switch (CallList[i].type) {
      
      case CallType::RBOX:
        m_renderer.renderBox(
          CallList[i].PD.pos,
          CallList[i].SD.width,
          CallList[i].SD.height,
          CallList[i].RD.color
        );
        break;
      case CallType::RBOXFILL:
        m_renderer.renderBoxFill(
          CallList[i].PD.pos,
          CallList[i].SD.width,
          CallList[i].SD.height,
          CallList[i].RD.color
        );
        break;
      case CallType::RCIRCLE:
        m_renderer.renderCircle(
          CallList[i].PD.pos,
          CallList[i].SD.radius,
          CallList[i].RD.color
        );
        break;
      case CallType::RCIRCLEFILL:
        m_renderer.renderCircleFill(
          CallList[i].PD.pos,
          CallList[i].SD.radius,
          CallList[i].RD.color
        );
        break;
      case CallType::SETDRAWCOLOR:
        m_renderer.setRenderColor(CallList[i].RD.color);
        break;
      case CallType::RTEXTURE:
        m_renderer.renderTexture(
          CallList[i].RD.texture,
          CallList[i].RD.uv,
          CallList[i].RD.layer,
          SDL_FRect{
            CallList[i].PD.pos.x,
            CallList[i].PD.pos.y,
            CallList[i].SD.width,
            CallList[i].SD.height,
          }
        );
      break;
      case CallType::RLINE:
        m_renderer.renderLine(
          CallList[i].PD.pos,
          CallList[i].PD.pos2,
          CallList[i].RD.color
        );
      break;
      case CallType::RFULLTEXTURE:
        m_renderer.renderTextureFull(
          CallList[i].RD.texture,
          CallList[i].RD.layer,
          SDL_FRect{
            CallList[i].PD.pos.x,
            CallList[i].PD.pos.y,
            CallList[i].SD.width,
            CallList[i].SD.height,
          }
        );
      break;
      case CallType::RGEOMETRY:
        m_renderer.renderGeometry(
          CallList[i].GD.verticies, 
          CallList[i].GD.numVerticies, 
          CallList[i].GD.indices, 
          CallList[i].GD.numIndices
      );
      case CallType::RPOINTS:
        m_renderer.renderPoints(
          CallList[i].GD.points,
          CallList[i].GD.numPoints
      );
    }
  }  
  CallList.clear();

  m_renderer.renderPresent();
  return true;  
};


}

}


