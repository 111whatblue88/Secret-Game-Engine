#include "ecs.hpp"
#include "../ELOgine.hpp"
#include <SDL3/SDL_pixels.h>
#include <algorithm>
#include <cstdint>

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>

using namespace elo;
using namespace ecs;

ecs::ComponentList<Transform> EntitySys::TransformComp = ecs::ComponentList<Transform>();
ecs::ComponentList<TextRenderer> EntitySys::TextRendererComp = ecs::ComponentList<TextRenderer>();

std::vector<uint32_t> EntitySys::validEntities = std::vector<uint32_t>();
uint32_t EntitySys::m_entityCount = 0;

uint32_t EntitySys::createEntity(Transform transform) {
  m_entityCount++;
  validEntities.push_back(m_entityCount);
  TransformComp.add(m_entityCount, transform);
  return m_entityCount;
}
std::vector<uint32_t> ecs::EntitySys::getEntityList() {
  return validEntities;
}

// Transform
Transform::Transform(Vector2 pos, float width, float height){
  this->pos=pos;
  this->width=width;
  this->height=height;
  ID=EntitySys::TransformComp.getComponentCount()+1;
}
Transform::Transform(Vector2 pos, float radius) {
  this->pos=pos;
  this->radius=radius;
}
uint32_t Transform::getID() {
  return ID;
}

// IMG Renderer 
ImgRenderer::ImgRenderer(std::string location, SDL_FRect uv, int layer) {
  texture = rend::RenderSys::m_renderer.textureFromImage(location);
  this->layer=layer;
  this->uv=uv;
};
ImgRenderer::ImgRenderer(std::string location, int layer) {
  texture = rend::RenderSys::m_renderer.textureFromImage(location);
  this->layer=layer;
};

// Text Renderer 
TextRenderer::TextRenderer(std::string fontLocation, std::string text, int size, Color color, int layer)
  :transform(Vector2(0,0),0,0)
{
  this->texture = rend::RenderSys::m_renderer.textureFromFont(
      fontLocation,
      size,
      color,
      text
  );
  this->layer=layer;
  this->inheritTransform = true;
};
uint32_t TextRenderer::getID() {
  return ID;
}

TextRenderer::TextRenderer(std::string fontLocation, std::string text, int size, Color color, int layer, Transform t)
  :transform(t)
{
  this->texture = rend::RenderSys::m_renderer.textureFromFont(
      fontLocation,
      size,
      color,
      text
  );
  this->layer=layer;
  this->inheritTransform = false;
};

bool TextRenderer::editText(std::string fontLocation, std::string text, int size, Color color) {
  this->texture = rend::RenderSys::m_renderer.textureFromFont(
      fontLocation,
      size,
      color,
      text
  );
  return true;
}

// Primitive Renderer
PrimitiveRenderer::PrimitiveRenderer(PrimitiveType type, Color color) {
  this->type=type;
  this->color=color;
};

// PhysicsBody
void PhysicsBody::PhysicsBody::addForce(Vector2 force) {
  velocity.x += force.x;
  velocity.y += force.y;
}

// basicCollider
BasicCollider::BasicCollider(Collidertype type, bool renderCollider) {
  this->type = type;
  this->renderCollider = renderCollider;
}


