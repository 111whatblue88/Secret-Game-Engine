#include "ecs.hpp"
#include "../HUGE.hpp"
#include <SDL3/SDL_pixels.h>
#include <algorithm>
#include <cstdint>

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
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
  this->name=name;
  this->texture = rend::RenderSys::m_renderer.textureFromImage(location);
  this->layer=layer;
  this->uv=uv;
}
ImgRenderer::ImgRenderer(std::string name,std::string location, int layer) {
  this->name=name;
  this->texture = rend::RenderSys::m_renderer.textureFromImage(location);
  this->layer=layer;
  this->uv={0,0,0,0};
}
ImgRenderer::ImgRenderer() {
  this->texture=NULL;
  this->layer=0;
  this->uv={0,0,0,0};
}
std::string const ImgRenderer::GetName() {
  return name;
}
bool ImgRenderer::SetName(std::string name) {
  this->name=name;
  return true;
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



