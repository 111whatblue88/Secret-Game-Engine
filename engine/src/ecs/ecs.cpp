#include "ecs.hpp"
#include "../HUGE.hpp"
#include "../../vendored/SDL/src/include/SDL3/SDL.h"
#include "../../vendored/SDL/src_ttf/include/SDL3_ttf/SDL_ttf.h"

#include <SDL3/SDL_gpu.h>
#include <algorithm>
#include <cstdint>
#include <string>
#include <sys/types.h>

using namespace huge;
using namespace ecs;
using namespace rend;

using ID = uint32_t;

// Transform
Transform::Transform(Vector2 pos, float width, float height){
  this->pos=pos;
  this->width=width;
  this->height=height;
}
Transform::Transform(Vector2 pos, float radius) {
  this->pos=pos;
  this->radius=radius;
}
Transform::Transform() {
  this->pos={0,0};
  this->width=0;
  this->height=0;
  this->radius=0;
}

// Component
std::string const Component::GetName() {
  return m_name;
}
bool Component::SetName(std::string name) {
  this->m_name=name;
  return true;
}

// IMG Renderer 
ImgRenderer::ImgRenderer(std::string location, SDL_FRect uv, int layer) {
  this->texture = rend::RenderSys::m_renderer.textureFromImage(location);
  this->layer=layer;
  this->uv=uv;
};
ImgRenderer::ImgRenderer(std::string location, int layer) {
  this->texture = rend::RenderSys::m_renderer.textureFromImage(location);
  this->layer=layer;
  this->uv={0,0,0,0};
};
ImgRenderer::ImgRenderer(std::string name, std::string location, SDL_FRect uv, int layer) {
  this->SetName(name);
  this->texture = rend::RenderSys::m_renderer.textureFromImage(location);
  this->layer=layer;
  this->uv=uv;
}
ImgRenderer::ImgRenderer(std::string name, std::string location, int layer) {
  this->SetName(name);
  this->texture = rend::RenderSys::m_renderer.textureFromImage(location);
  this->layer=layer;
  this->uv={0,0,0,0};
}
ImgRenderer::ImgRenderer() {
  this->texture=NULL;
  this->layer=0;
  this->uv={0,0,0,0};
}

// Primitive Renderer 
PrimitiveRenderer::PrimitiveRenderer(PrimitiveType type, Color color) {
this->SetName("defaultName");
this->type = type;
this->color = color;
this->firstPoint = {0,0};
this->secondPoint = {0,0};
}
PrimitiveRenderer::PrimitiveRenderer(PrimitiveType type, Color color, Vector2 p1, Vector2 p2) {
this->SetName("defaultName");
this->type = type;
this->color = color;
this->firstPoint = p1;
this->secondPoint = p2;
}
PrimitiveRenderer::PrimitiveRenderer(std::string name, PrimitiveType type, Color color) {
this->SetName(name);
this->type = type;
this->color = color;
this->firstPoint = {0,0};
this->secondPoint = {0,0};
}
PrimitiveRenderer::PrimitiveRenderer(std::string name, PrimitiveType type, Color color, Vector2 p1, Vector2 p2) {
this->SetName(name);
this->type = type;
this->color = color;
this->firstPoint = p1;
this->secondPoint = p2;
}
PrimitiveRenderer::PrimitiveRenderer() {
this->SetName("defaultName");
this->type=PrimitiveType::line;
this->color=Color(0,0,0);
this->firstPoint = {0,0};
this->secondPoint = {0,0};
}

// Text Renderer
TextRenderer::TextRenderer(std::string fontLocation, std::string text, int size, Color color, int layer) {
  this->SetName("defaultName");
  this->fontLocation=fontLocation;
  this->text=text;
  this->size=size;
  this->color=color;
  this->layer=layer;

  this->font = rend::RenderSys::m_renderer.createFont(fontLocation, size);
  this->texture=rend::RenderSys::m_renderer.textureFromFont(font ,color,text);
}
TextRenderer::TextRenderer(std::string name, std::string fontLocation, std::string text, int size, Color color, int layer) {
  this->SetName(name);
  this->fontLocation=fontLocation;
  this->text=text;
  this->size=size;
  this->color=color;
  this->layer=layer;

  this->font = rend::RenderSys::m_renderer.createFont(fontLocation, size);
  this->texture=rend::RenderSys::m_renderer.textureFromFont(font,color,text);
}

TextRenderer::TextRenderer() {
  this->SetName("defaultName");
  this->fontLocation="";
  this->text="";
  this->size=0;
  this->color={0, 0,0};
  this->layer=0;

  this->font = rend::RenderSys::m_renderer.createFont(fontLocation, size);

  this->texture=nullptr;
}

bool TextRenderer::editFont(std::string fontLocation) {
  this->fontLocation = fontLocation;
  this->texture = rend::RenderSys::m_renderer.textureFromFont(fontLocation, size, color, text);
  if (!texture) {
    return false;
  } else {
    return true;
  }
}
bool TextRenderer::editSize(int size) {
  this->size=size;
  this->texture = rend::RenderSys::m_renderer.textureFromFont(fontLocation, size, color, text);
  if (!texture) {
    return false;
  } else {
    return true;
  }
}
bool TextRenderer::editText(std::string text) {
  this->text=text;
  this->texture = rend::RenderSys::m_renderer.textureFromFont(font, color, text);
  if (!texture) {
    return false;
  } else {
    return true;
  }
}
bool TextRenderer::editColor(Color color) {
  this->color=color;
  this->texture = rend::RenderSys::m_renderer.textureFromFont(font, color, text);
  if (!texture) {
    return false;
  } else {
    return true;
  }
}

// Physics Body
PhysicsBody::PhysicsBody() {
}
Vector2 PhysicsBody::getVelocity() {
  return m_velocity;
}
void PhysicsBody::addForce(Vector2 force) {
  m_velocity.x += force.x;
  m_velocity.y += force.y;
}


// Entity struct
bool Entity::SetName(std::string name) {
  this->name=name;
  return true;
}
std::string const Entity::GetName() {
  return name;
}
Entity::Entity() {
  this->name = "defaultName";
  this->TransformComp = Transform(Vector2(20,20),20,20);
}
Entity::Entity(class Transform transform) {
  this->name = "defaultName";
  this->TransformComp = transform;
}
Entity::Entity(std::string name, class Transform transform) {
  this->name = name;
  this->TransformComp = transform;
}

// EntitySys
std::unordered_map<uint32_t, Entity> EntitySys::m_entityList = {};
uint32_t EntitySys::m_entityCount = 0;
Entity& EntitySys::CreateEntity(Transform transform) {
  m_entityCount++;
  m_entityList.emplace(m_entityCount, Entity(transform));
  return m_entityList[m_entityCount];
}
std::unordered_map<uint32_t, Entity>& EntitySys::GetEntityList() {
  return m_entityList;
}
bool EntitySys::update() {
  
  auto& EList = EntitySys::GetEntityList();

  for (auto E : EList) {

    E.second.TransformComp.pos.x += E.second.PhysicsBodyComp.getVelocity().x;
    E.second.TransformComp.pos.y += E.second.PhysicsBodyComp.getVelocity().y;

    // img renderer
    if (E.second.ImgRendererComp.has()) {
      for (auto IR : E.second.ImgRendererComp.getComponentList()) {

        IR.second.transform.height = IR.second.transform.height == 0 ? E.second.TransformComp.height: IR.second.transform.height;
        IR.second.transform.width = IR.second.transform.width == 0 ? E.second.TransformComp.width : IR.second.transform.width;

        if (IR.second.uv.x || IR.second.uv.y || IR.second.uv.w || IR.second.uv.h) {
          RenderSys::CallList.push_back(RenderSys::RenderCall{
            RenderSys::CallType::RTEXTURE,
            RenderSys::PositionalData{(E.second.TransformComp.pos + IR.second.transform.pos)},
            RenderSys::SizeData{IR.second.transform.width, IR.second.transform.height},
            RenderSys::RenderingData{Color(0,0,0),IR.second.texture, IR.second.uv,0}
          });
        } else {
          if (!IR.second.texture) {
          }
          RenderSys::CallList.push_back(RenderSys::RenderCall{
            RenderSys::CallType::RFULLTEXTURE,
            RenderSys::PositionalData{(E.second.TransformComp.pos + IR.second.transform.pos)},
            RenderSys::SizeData{IR.second.transform.width, IR.second.transform.height},
            RenderSys::RenderingData{Color(0,0,0),IR.second.texture, 0,0,0,0,0}
          });
        }
      }
    }

    // primitve renderer
    if (E.second.PrimitiveRendererComp.has()) {
      for (auto PR : E.second.PrimitiveRendererComp.getComponentList()) {
        PR.second.transform.height = PR.second.transform.height == 0 ? E.second.TransformComp.height: PR.second.transform.height;
        PR.second.transform.width = PR.second.transform.width == 0 ? E.second.TransformComp.width : PR.second.transform.width;
        PR.second.transform.radius= PR.second.transform.radius== 0 ? E.second.TransformComp.radius: PR.second.transform.radius;
        switch (PR.second.type) {
          case ecs::PrimitiveRenderer::PrimitiveType::square: {
            RenderSys::CallList.push_back(RenderSys::RenderCall{
              RenderSys::CallType::RBOX,
              RenderSys::PositionalData{E.second.TransformComp.pos+PR.second.transform.pos},
              RenderSys::SizeData{PR.second.transform.width, PR.second.transform.height},
              RenderSys::RenderingData{PR.second.color}
            });
            break;
          }
          case ecs::PrimitiveRenderer::PrimitiveType::squareFill: {
            RenderSys::CallList.push_back(RenderSys::RenderCall{
              RenderSys::CallType::RBOXFILL,
              RenderSys::PositionalData{E.second.TransformComp.pos+PR.second.transform.pos},
              RenderSys::SizeData{PR.second.transform.width, PR.second.transform.height},
              RenderSys::RenderingData{PR.second.color}
            });
            break;
          }
          case ecs::PrimitiveRenderer::PrimitiveType::circle: {
            RenderSys::CallList.push_back(RenderSys::RenderCall{
              RenderSys::CallType::RCIRCLE,
              RenderSys::PositionalData{E.second.TransformComp.pos+PR.second.transform.pos},
              RenderSys::SizeData{0,0,PR.second.transform.radius},
              RenderSys::RenderingData{PR.second.color}
            });
            break;
          }
          case ecs::PrimitiveRenderer::PrimitiveType::circleFill: {
            RenderSys::CallList.push_back(RenderSys::RenderCall{
              RenderSys::CallType::RCIRCLEFILL,
              RenderSys::PositionalData{E.second.TransformComp.pos+PR.second.transform.pos},
              RenderSys::SizeData{0,0,PR.second.transform.radius},
              RenderSys::RenderingData{PR.second.color}
            });
            break;
          }
          case ecs::PrimitiveRenderer::PrimitiveType::line: {
            RenderSys::CallList.push_back(RenderSys::RenderCall{
              RenderSys::CallType::RLINE,
              RenderSys::PositionalData{PR.second.firstPoint, PR.second.secondPoint},
              RenderSys::SizeData{},
              RenderSys::RenderingData{PR.second.color}
            });
            break;
          }
        }
      }      
    }

    // Text Renderer
    if (E.second.TextRendererComp.has()) {
      for (auto TR : E.second.TextRendererComp.getComponentList()) {
        TR.second.transform.height = TR.second.transform.height == 0 ? E.second.TransformComp.height: TR.second.transform.height;
        TR.second.transform.width = TR.second.transform.width == 0 ? E.second.TransformComp.width : TR.second.transform.width;
        RenderSys::CallList.push_back(RenderSys::RenderCall{
          RenderSys::CallType::RFULLTEXTURE,
          RenderSys::PositionalData{(E.second.TransformComp.pos + TR.second.transform.pos)},
          RenderSys::SizeData{TR.second.transform.width, TR.second.transform.height},
          RenderSys::RenderingData{{0,0,0}, TR.second.texture}
        });
      }
    }








  }
  return true;
};



