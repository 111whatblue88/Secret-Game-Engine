#include "ecs.hpp"
#include "../HUGE.hpp"
#include "../../vendored/SDL/src/include/SDL3/SDL.h"
#include "../../vendored/SDL/src_ttf/include/SDL3_ttf/SDL_ttf.h"

#include <algorithm>
#include <cstdint>
#include <string>
#include <sys/types.h>

using namespace huge;
using namespace ecs;

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
  return name;
}
bool Component::SetName(std::string name) {
  this->name=name;
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
this->name="defaultName";
this->type = type;
this->color = color;
this->LineTypeSecondPoint = {0,0};
}
PrimitiveRenderer::PrimitiveRenderer(PrimitiveType type, Color color, Vector2 vec) {
this->name="defaultName";
this->type = type;
this->color = color;
this->LineTypeSecondPoint = vec;
}
PrimitiveRenderer::PrimitiveRenderer(std::string name, PrimitiveType type, Color color) {
this->name=name;
this->type = type;
this->color = color;
this->LineTypeSecondPoint = {0,0};
}
PrimitiveRenderer::PrimitiveRenderer(std::string name, PrimitiveType type, Color color, Vector2 vec) {
this->name=name;
this->type = type;
this->color = color;
this->LineTypeSecondPoint = vec;
}
PrimitiveRenderer::PrimitiveRenderer() {
this->name="defaultName";
this->type=PrimitiveType::line;
this->color=Color(0,0,0);
this->LineTypeSecondPoint = {0,0};
}
std::string const PrimitiveRenderer::GetName() {
  return name;
}
bool PrimitiveRenderer::SetName(std::string name) {
  this->name=name;
  return true;
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
  // if you want to know why this is empty, bad things happened here
  return true;
};



