#include "ecs.hpp"
#include "../ELOgine.hpp"
#include <SDL3/SDL_pixels.h>
#include <cstdint>

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>

using namespace elo;
using namespace ecs;

std::vector<uint32_t> EntitySys::validEntities = std::vector<uint32_t>();
uint32_t EntitySys::m_entityCount = 0;

uint32_t EntitySys::addEntity(Transform init) {
  uint32_t ID = m_entityCount;
  validEntities.push_back(ID);
  m_entityCount++;

  TransformComponent::add(ID, init);

  return ID;
}
void EntitySys::remEntity(uint32_t entityID) {
  validEntities[findEntity(entityID)] = std::move(validEntities.back());
  validEntities.pop_back();
}
size_t const EntitySys::findEntity(uint32_t ID) {
  for (size_t i = 0; i < validEntities.size(); i++) {
    if (validEntities[i] == ID) {
      return i;
    }
  }
  return -1;
}
std::vector<uint32_t> EntitySys::getEntityList() {
  return validEntities;
}


// Transform
std::unordered_map<uint32_t, Transform> TransformComponent::entityList = std::unordered_map<uint32_t, Transform>();
Transform::Transform(Vector2 pos, float width, float height){
  this->pos=pos;
  this->width=width;
  this->height=height;
}
Transform::Transform(Vector2 pos, float radius) {
  this->pos=pos;
  this->radius=radius;
}
void TransformComponent::add(uint32_t entityID, Transform transformInit) {
  entityList.emplace(entityID, transformInit);
}
Transform &TransformComponent::get(uint32_t entityID) {
  return entityList.at(entityID);
}
bool const TransformComponent::has(uint32_t entityID) {
  if (entityList.contains(entityID)) {
    return true;
  } else {
    return false;
  }
}

// IMG Renderer 
std::unordered_map<uint32_t, ImgRenderer> ImgRendererComp::entityList = std::unordered_map<uint32_t, ImgRenderer>();
ImgRenderer::ImgRenderer(std::string location, SDL_FRect uv, int layer) {
  texture = rend::RenderSys::m_renderer.textureFromImage(location);
  this->layer=layer;
  this->uv=uv;
};
ImgRenderer::ImgRenderer(std::string location, int layer) {
  texture = rend::RenderSys::m_renderer.textureFromImage(location);
  this->layer=layer;
};
void ImgRendererComp::add(uint32_t entityID, ImgRenderer ir) {
  entityList.emplace(entityID, ir);
}
void ImgRendererComp::rem(uint32_t entityID) {
  entityList.erase(entityID);
}
ImgRenderer& ImgRendererComp::get(uint32_t entityID) {
  return entityList.at(entityID);
}
bool const ImgRendererComp::has(uint32_t entityID) {
  if (entityList.contains(entityID)) {
    return true;
  } else {
    return false;
  }
}
std::unordered_map<uint32_t, ImgRenderer> ImgRendererComp::getEntityList() {
  return entityList;
};

// Text Renderer 
std::unordered_map<uint32_t, TextRenderer> TextRendererComp::entityList = std::unordered_map<uint32_t, TextRenderer>();
TextRenderer::TextRenderer(std::string fontLocation, std::string text, int size, Color color, int layer) {
  
  this->texture = rend::RenderSys::m_renderer.textureFromFont(
      fontLocation,
      size,
      color,
      text
  );

  this->layer=layer;
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
void TextRendererComp::add(uint32_t entityID, TextRenderer ir) {
  entityList.emplace(entityID, ir);
}
void TextRendererComp::rem(uint32_t entityID) {
  entityList.erase(entityID);
}
TextRenderer& TextRendererComp::get(uint32_t entityID) {
  return entityList.at(entityID);
}
bool const TextRendererComp::has(uint32_t entityID) {
  if (entityList.contains(entityID)) {
    return true;
  } else {
    return false;
  }
}
std::unordered_map<uint32_t, TextRenderer> TextRendererComp::getEntityList() {
  return entityList;
};

// Primitive Renderer
std::unordered_map<uint32_t, PrimitiveRenderer> PrimitiveRendererComponent::entityList = std::unordered_map<uint32_t, PrimitiveRenderer>();
PrimitiveRenderer::PrimitiveRenderer(PrimitiveType type, Color color) {
  this->type=type;
  this->color=color;
};
void PrimitiveRendererComponent::add(uint32_t entityID, PrimitiveRenderer pr) {
  entityList.emplace(entityID, pr);
}
void PrimitiveRendererComponent::rem(uint32_t entityID) {
  entityList.erase(entityID);
}
PrimitiveRenderer& PrimitiveRendererComponent::get(uint32_t entityID) {
  return entityList.at(entityID);
}
bool const PrimitiveRendererComponent::has(uint32_t entityID) {
  if (entityList.contains(entityID)) {
    return true;
  } else {
    return false;
  }
}
std::unordered_map<uint32_t, PrimitiveRenderer> PrimitiveRendererComponent::getEntityList() {
  return entityList;
};

// PhysicsBody
std::unordered_map<uint32_t, PhysicsBody> PhysicsBodyComponent::entityList = std::unordered_map<uint32_t, PhysicsBody>();
void PhysicsBody::PhysicsBody::addForce(Vector2 force) {
  velocity.x += force.x;
  velocity.y += force.y;
}
void PhysicsBodyComponent::add(uint32_t entityID, PhysicsBody pb) {
  entityList.emplace(entityID, pb);
}
void PhysicsBodyComponent::rem(uint32_t entityID) {
  entityList.erase(entityID);
}
PhysicsBody& PhysicsBodyComponent::get(uint32_t entityID) {
  return entityList.at(entityID);
}
bool const PhysicsBodyComponent::has(uint32_t entityID) {
  if (entityList.contains(entityID)) {
    return true;
  } else {
    return false;
  }
}
std::unordered_map<uint32_t, PhysicsBody> PhysicsBodyComponent::getEntityList() {
  return entityList;
};

// basicCollider
std::unordered_map<uint32_t, BasicCollider> BasicColliderComponent::entityList = std::unordered_map<uint32_t, BasicCollider>();
BasicCollider::BasicCollider(Collidertype type, bool renderCollider) {
  this->type = type;
  this->renderCollider = renderCollider;
}
void BasicColliderComponent::add(uint32_t entityID, BasicCollider bc) {
  entityList.emplace(entityID, bc);
}
void BasicColliderComponent::rem(uint32_t entityID) {
  entityList.erase(entityID);
}
BasicCollider& BasicColliderComponent::get(uint32_t entityID) {
  return entityList.at(entityID);
}
bool const BasicColliderComponent::has(uint32_t entityID) {
  if (entityList.contains(entityID)) {
    return true;
  } else {
    return false;
  }
}
bool BasicColliderComponent::isColliding(uint32_t e1, uint32_t e2) {
  ecs::BasicCollider& e1Collider = ecs::BasicColliderComponent::get(e1);
  ecs::BasicCollider& e2Collider = ecs::BasicColliderComponent::get(e2);

  if (e1Collider.type == ecs::BasicCollider::Collidertype::circleCollider && 
      e2Collider.type == ecs::BasicCollider::Collidertype::boxCollider ||
      e2Collider.type == ecs::BasicCollider::Collidertype::boxCollider && 
      e1Collider.type == ecs::BasicCollider::Collidertype::circleCollider
  ) {
    // circle && box 

  } else if (
    e2Collider.type == ecs::BasicCollider::Collidertype::boxCollider && 
    e1Collider.type == ecs::BasicCollider::Collidertype::boxCollider
  ) {
    // box on box

  } else if (
    e2Collider.type == ecs::BasicCollider::Collidertype::circleCollider && 
    e1Collider.type == ecs::BasicCollider::Collidertype::circleCollider
  ) {
    // circle on circle 
    
  }

  return false;
}
std::unordered_map<uint32_t, BasicCollider> BasicColliderComponent::getEntityList() {
  return entityList;
};


